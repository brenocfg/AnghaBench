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
struct usbip_iso_packet_descriptor {int dummy; } ;
struct urb {int number_of_packets; int /*<<< orphan*/ * iso_frame_desc; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_iso_pakcet_correct_endian (struct usbip_iso_packet_descriptor*,int) ; 
 int /*<<< orphan*/  usbip_pack_iso (struct usbip_iso_packet_descriptor*,int /*<<< orphan*/ *,int) ; 

void *usbip_alloc_iso_desc_pdu(struct urb *urb, ssize_t *bufflen)
{
	void *buff;
	struct usbip_iso_packet_descriptor *iso;
	int np = urb->number_of_packets;
	ssize_t size = np * sizeof(*iso);
	int i;

	buff = kzalloc(size, GFP_KERNEL);
	if (!buff)
		return NULL;

	for (i = 0; i < np; i++) {
		iso = buff + (i * sizeof(*iso));

		usbip_pack_iso(iso, &urb->iso_frame_desc[i], 1);
		usbip_iso_pakcet_correct_endian(iso, 1);
	}

	*bufflen = size;

	return buff;
}