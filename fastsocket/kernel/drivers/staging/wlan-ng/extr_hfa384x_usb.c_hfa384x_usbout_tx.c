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
typedef  int /*<<< orphan*/  hfa384x_usbout_t ;

/* Variables and functions */
 int /*<<< orphan*/  prism2sta_ev_alloc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hfa384x_usbout_tx(wlandevice_t *wlandev, hfa384x_usbout_t *usbout)
{
	prism2sta_ev_alloc(wlandev);
}