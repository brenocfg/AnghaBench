#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct wpabuf {int dummy; } ;
struct eap_hdr {int /*<<< orphan*/  length; } ;
typedef  scalar_t__ const EapType ;

/* Variables and functions */
 scalar_t__ const EAP_TYPE_EXPANDED ; 
 int EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int WPA_GET_BE24 (scalar_t__ const*) ; 
 scalar_t__ WPA_GET_BE32 (scalar_t__ const*) ; 
 size_t be_to_host16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_hdr_len_valid (struct wpabuf const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct eap_hdr* wpabuf_head (struct wpabuf const*) ; 

const u8 * eap_hdr_validate(int vendor, EapType eap_type,
			    const struct wpabuf *msg, size_t *plen)
{
	const struct eap_hdr *hdr;
	const u8 *pos;
	size_t len;

	if (!eap_hdr_len_valid(msg, 1))
		return NULL;

	hdr = wpabuf_head(msg);
	len = be_to_host16(hdr->length);
	pos = (const u8 *) (hdr + 1);

	if (*pos == EAP_TYPE_EXPANDED) {
		int exp_vendor;
		u32 exp_type;
		if (len < sizeof(*hdr) + 8) {
			wpa_printf(MSG_INFO, "EAP: Invalid expanded EAP "
				   "length");
			return NULL;
		}
		pos++;
		exp_vendor = WPA_GET_BE24(pos);
		pos += 3;
		exp_type = WPA_GET_BE32(pos);
		pos += 4;
		if (exp_vendor != vendor || exp_type != (u32) eap_type) {
			wpa_printf(MSG_INFO, "EAP: Invalid expanded frame "
				   "type");
			return NULL;
		}

		*plen = len - sizeof(*hdr) - 8;
		return pos;
	} else {
		if (vendor != EAP_VENDOR_IETF || *pos != eap_type) {
			wpa_printf(MSG_INFO, "EAP: Invalid frame type");
			return NULL;
		}
		*plen = len - sizeof(*hdr) - 1;
		return pos + 1;
	}
}