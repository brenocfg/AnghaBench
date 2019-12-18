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
 int /*<<< orphan*/ * ipx_interfaces_head () ; 
 int /*<<< orphan*/ * ipx_primary_net ; 
 scalar_t__ ipxcfg_auto_select_primary ; 

__attribute__((used)) static void ipxitf_clear_primary_net(void)
{
	ipx_primary_net = NULL;
	if (ipxcfg_auto_select_primary)
		ipx_primary_net = ipx_interfaces_head();
}