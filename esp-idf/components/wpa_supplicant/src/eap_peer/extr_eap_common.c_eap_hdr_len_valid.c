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
struct wpabuf {int dummy; } ;
struct eap_hdr {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 size_t be_to_host16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct eap_hdr* wpabuf_head (struct wpabuf const*) ; 
 size_t wpabuf_len (struct wpabuf const*) ; 

int eap_hdr_len_valid(const struct wpabuf *msg, size_t min_payload)
{
	const struct eap_hdr *hdr;
	size_t len;

	if (msg == NULL)
		return 0;

	hdr = wpabuf_head(msg);

	if (wpabuf_len(msg) < sizeof(*hdr)) {
		wpa_printf(MSG_INFO, "EAP: Too short EAP frame");
		return 0;
	}

	len = be_to_host16(hdr->length);
	if (len < sizeof(*hdr) + min_payload || len > wpabuf_len(msg)) {
		wpa_printf(MSG_INFO, "EAP: Invalid EAP length");
		return 0;
	}

	return 1;
}