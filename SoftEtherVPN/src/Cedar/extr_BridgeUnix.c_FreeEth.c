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
 int /*<<< orphan*/  FreeStrList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * eth_offload_list ; 

void FreeEth()
{
	if (eth_offload_list != NULL)
	{
		FreeStrList(eth_offload_list);
		eth_offload_list = NULL;
	}
}