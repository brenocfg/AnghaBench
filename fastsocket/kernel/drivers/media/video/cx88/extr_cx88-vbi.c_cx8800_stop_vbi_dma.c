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
struct cx8800_dev {struct cx88_core* core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MO_PCI_INTMSK ; 
 int /*<<< orphan*/  MO_VID_DMACNTRL ; 
 int /*<<< orphan*/  MO_VID_INTMSK ; 
 int PCI_INT_VIDINT ; 
 int /*<<< orphan*/  VID_CAPTURE_CONTROL ; 
 int /*<<< orphan*/  cx_clear (int /*<<< orphan*/ ,int) ; 

int cx8800_stop_vbi_dma(struct cx8800_dev *dev)
{
	struct cx88_core *core = dev->core;

	/* stop dma */
	cx_clear(MO_VID_DMACNTRL, 0x88);

	/* disable capture */
	cx_clear(VID_CAPTURE_CONTROL,0x18);

	/* disable irqs */
	cx_clear(MO_PCI_INTMSK, PCI_INT_VIDINT);
	cx_clear(MO_VID_INTMSK, 0x0f0088);
	return 0;
}