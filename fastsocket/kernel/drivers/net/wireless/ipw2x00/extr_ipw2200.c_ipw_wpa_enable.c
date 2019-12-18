#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ipw_priv {TYPE_1__* ieee; } ;
struct TYPE_2__ {int wpa_enabled; } ;

/* Variables and functions */

__attribute__((used)) static int ipw_wpa_enable(struct ipw_priv *priv, int value)
{
	/* This is called when wpa_supplicant loads and closes the driver
	 * interface. */
	priv->ieee->wpa_enabled = value;
	return 0;
}