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
struct savagefb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VGAwSEQ (int,int,struct savagefb_par*) ; 

__attribute__((used)) static void vgaHWSeqReset(struct savagefb_par *par, int start)
{
	if (start)
		VGAwSEQ(0x00, 0x01, par);	/* Synchronous Reset */
	else
		VGAwSEQ(0x00, 0x03, par);	/* End Reset */
}