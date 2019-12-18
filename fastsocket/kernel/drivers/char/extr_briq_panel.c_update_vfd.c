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

/* Variables and functions */
 scalar_t__ BRIQ_PANEL_VFD_IOPORT ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int* vfd ; 

__attribute__((used)) static void update_vfd(void)
{
	int	i;

	/* cursor home */
	outb(0x02, BRIQ_PANEL_VFD_IOPORT);
	for (i=0; i<20; i++)
		outb(vfd[i], BRIQ_PANEL_VFD_IOPORT + 1);

	/* cursor to next line */
	outb(0xc0, BRIQ_PANEL_VFD_IOPORT);
	for (i=20; i<40; i++)
		outb(vfd[i], BRIQ_PANEL_VFD_IOPORT + 1);

}