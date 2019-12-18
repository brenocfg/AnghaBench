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
typedef  int /*<<< orphan*/  wlandevice_t ;
typedef  int /*<<< orphan*/  hfa384x_InfFrame_t ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void prism2sta_inf_handover(wlandevice_t *wlandev,
				   hfa384x_InfFrame_t *inf)
{
	pr_debug("received infoframe:HANDOVER (unhandled)\n");
	return;
}