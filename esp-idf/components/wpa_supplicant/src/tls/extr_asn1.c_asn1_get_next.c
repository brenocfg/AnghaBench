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
typedef  int u8 ;
struct asn1_hdr {int identifier; int class; int constructed; int tag; int length; int const* payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_memset (struct asn1_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int asn1_get_next(const u8 *buf, size_t len, struct asn1_hdr *hdr)
{
	const u8 *pos, *end;
	u8 tmp;

	os_memset(hdr, 0, sizeof(*hdr));
	pos = buf;
	end = buf + len;

	hdr->identifier = *pos++;
	hdr->class = hdr->identifier >> 6;
	hdr->constructed = !!(hdr->identifier & (1 << 5));

	if ((hdr->identifier & 0x1f) == 0x1f) {
		hdr->tag = 0;
		do {
			if (pos >= end) {
				wpa_printf(MSG_DEBUG, "ASN.1: Identifier "
					   "underflow");
				return -1;
			}
			tmp = *pos++;
			wpa_printf(MSG_DEBUG, "ASN.1: Extended tag data: "
				   "0x%02x", tmp);
			hdr->tag = (hdr->tag << 7) | (tmp & 0x7f);
		} while (tmp & 0x80);
	} else
		hdr->tag = hdr->identifier & 0x1f;

	tmp = *pos++;
	if (tmp & 0x80) {
		if (tmp == 0xff) {
			wpa_printf(MSG_DEBUG, "ASN.1: Reserved length "
				   "value 0xff used");
			return -1;
		}
		tmp &= 0x7f; /* number of subsequent octets */
		hdr->length = 0;
		if (tmp > 4) {
			wpa_printf(MSG_DEBUG, "ASN.1: Too long length field");
			return -1;
		}
		while (tmp--) {
			if (pos >= end) {
				wpa_printf(MSG_DEBUG, "ASN.1: Length "
					   "underflow");
				return -1;
			}
			hdr->length = (hdr->length << 8) | *pos++;
		}
	} else {
		/* Short form - length 0..127 in one octet */
		hdr->length = tmp;
	}

	if (end < pos || hdr->length > (unsigned int) (end - pos)) {
		wpa_printf(MSG_DEBUG, "ASN.1: Contents underflow");
		return -1;
	}

	hdr->payload = pos;
	return 0;
}