#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ priv; } ;
typedef  TYPE_1__ wlandevice_t ;
struct TYPE_8__ {int scanflag; int /*<<< orphan*/  cmdq; int /*<<< orphan*/  scanresults; } ;
typedef  TYPE_2__ hfa384x_t ;
struct TYPE_9__ {int framelen; } ;
typedef  TYPE_3__ hfa384x_InfFrame_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void prism2sta_inf_hostscanresults(wlandevice_t *wlandev,
					  hfa384x_InfFrame_t *inf)
{
	hfa384x_t *hw = (hfa384x_t *) wlandev->priv;
	int nbss;

	nbss = (inf->framelen - 3) / 32;
	pr_debug("Received %d hostscan results\n", nbss);

	if (nbss > 32)
		nbss = 32;

	kfree(hw->scanresults);

	hw->scanresults = kmalloc(sizeof(hfa384x_InfFrame_t), GFP_ATOMIC);
	memcpy(hw->scanresults, inf, sizeof(hfa384x_InfFrame_t));

	if (nbss == 0)
		nbss = -1;

	/* Notify/wake the sleeping caller. */
	hw->scanflag = nbss;
	wake_up_interruptible(&hw->cmdq);
}