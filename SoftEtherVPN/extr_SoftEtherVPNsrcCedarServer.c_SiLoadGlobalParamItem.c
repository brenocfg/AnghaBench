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
typedef  size_t UINT ;

/* Variables and functions */
 size_t* vpn_global_parameters ; 

void SiLoadGlobalParamItem(UINT id, UINT value)
{
	// Validate arguments
	if (id == 0)
	{
		return;
	}

	vpn_global_parameters[id] = value;
}