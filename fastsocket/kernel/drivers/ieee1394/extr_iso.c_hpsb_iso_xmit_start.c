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
struct hpsb_iso {scalar_t__ type; int flags; int xmit_cycle; int buf_packets; int prebuffer; int start_cycle; } ;

/* Variables and functions */
 int HPSB_ISO_DRIVER_STARTED ; 
 scalar_t__ HPSB_ISO_XMIT ; 

int hpsb_iso_xmit_start(struct hpsb_iso *iso, int cycle, int prebuffer)
{
	if (iso->type != HPSB_ISO_XMIT)
		return -1;

	if (iso->flags & HPSB_ISO_DRIVER_STARTED)
		return 0;

	if (cycle < -1)
		cycle = -1;
	else if (cycle >= 8000)
		cycle %= 8000;

	iso->xmit_cycle = cycle;

	if (prebuffer < 0)
		prebuffer = iso->buf_packets - 1;
	else if (prebuffer == 0)
		prebuffer = 1;

	if (prebuffer >= iso->buf_packets)
		prebuffer = iso->buf_packets - 1;

	iso->prebuffer = prebuffer;

	/* remember the starting cycle; DMA will commence from xmit_queue_packets()
	   once enough packets have been buffered */
	iso->start_cycle = cycle;

	return 0;
}