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
struct usb_iso_packet_descriptor {scalar_t__ actual_length; int /*<<< orphan*/  status; } ;
struct urb {int number_of_packets; struct usb_iso_packet_descriptor* iso_frame_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOVERFLOW ; 
 int GET_NONE ; 
 int GET_SUCCESS ; 
 int GET_TOO_MUCH_BUBBLE ; 
 int GET_TRAILER ; 
 scalar_t__ ISO_PKT_SIZE ; 

__attribute__((used)) static int get_chunk(int start, struct urb *urb,
			int *head, int *tail, int *bubble_err)
{
	struct usb_iso_packet_descriptor *pkt = NULL;
	int ret = GET_SUCCESS;

	for (*head = *tail = -1; start < urb->number_of_packets; start++) {
		pkt = &urb->iso_frame_desc[start];

		/* handle the bubble of the Hub */
		if (-EOVERFLOW == pkt->status) {
			if (++*bubble_err > urb->number_of_packets / 3)
				return GET_TOO_MUCH_BUBBLE;
			continue;
		}

		/* This is the gap */
		if (pkt->status || pkt->actual_length <= 0
				|| pkt->actual_length > ISO_PKT_SIZE) {
			if (*head != -1)
				break;
			continue;
		}

		/* a good isochronous packet */
		if (pkt->actual_length == ISO_PKT_SIZE) {
			if (*head == -1)
				*head = start;
			*tail = start;
			continue;
		}

		/* trailer is here */
		if (pkt->actual_length < ISO_PKT_SIZE) {
			if (*head == -1) {
				*head = start;
				*tail = start;
				return GET_TRAILER;
			}
			break;
		}
	}

	if (*head == -1 && *tail == -1)
		ret = GET_NONE;
	return ret;
}