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
struct usb_ov511 {int /*<<< orphan*/  decomp_ops; } ;
struct ov511_frame {int dummy; } ;

/* Variables and functions */
 scalar_t__ request_decompressor (struct usb_ov511*) ; 

__attribute__((used)) static void
decompress(struct usb_ov511 *ov, struct ov511_frame *frame,
	   unsigned char *pIn0, unsigned char *pOut0)
{
	if (!ov->decomp_ops)
		if (request_decompressor(ov))
			return;

}