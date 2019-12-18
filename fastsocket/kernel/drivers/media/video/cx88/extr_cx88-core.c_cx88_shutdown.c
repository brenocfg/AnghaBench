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
struct cx88_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MO_AUD_DMACNTRL ; 
 int /*<<< orphan*/  MO_AUD_INTMSK ; 
 int /*<<< orphan*/  MO_DEV_CNTRL2 ; 
 int /*<<< orphan*/  MO_GPHST_DMACNTRL ; 
 int /*<<< orphan*/  MO_GPHST_INTMSK ; 
 int /*<<< orphan*/  MO_PCI_INTMSK ; 
 int /*<<< orphan*/  MO_TS_DMACNTRL ; 
 int /*<<< orphan*/  MO_TS_INTMSK ; 
 int /*<<< orphan*/  MO_VID_DMACNTRL ; 
 int /*<<< orphan*/  MO_VID_INTMSK ; 
 int /*<<< orphan*/  MO_VIP_DMACNTRL ; 
 int /*<<< orphan*/  MO_VIP_INTMSK ; 
 int /*<<< orphan*/  VID_CAPTURE_CONTROL ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 

void cx88_shutdown(struct cx88_core *core)
{
	/* disable RISC controller + IRQs */
	cx_write(MO_DEV_CNTRL2, 0);

	/* stop dma transfers */
	cx_write(MO_VID_DMACNTRL, 0x0);
	cx_write(MO_AUD_DMACNTRL, 0x0);
	cx_write(MO_TS_DMACNTRL, 0x0);
	cx_write(MO_VIP_DMACNTRL, 0x0);
	cx_write(MO_GPHST_DMACNTRL, 0x0);

	/* stop interrupts */
	cx_write(MO_PCI_INTMSK, 0x0);
	cx_write(MO_VID_INTMSK, 0x0);
	cx_write(MO_AUD_INTMSK, 0x0);
	cx_write(MO_TS_INTMSK, 0x0);
	cx_write(MO_VIP_INTMSK, 0x0);
	cx_write(MO_GPHST_INTMSK, 0x0);

	/* stop capturing */
	cx_write(VID_CAPTURE_CONTROL, 0);
}