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
typedef  int /*<<< orphan*/  PSDevice ;

/* Variables and functions */
 int wpa_init_wpadev (int /*<<< orphan*/ ) ; 
 int wpa_release_wpadev (int /*<<< orphan*/ ) ; 

int wpa_set_wpadev(PSDevice pDevice, int val)
{
	if (val)
		return wpa_init_wpadev(pDevice);
	else
		return wpa_release_wpadev(pDevice);
}