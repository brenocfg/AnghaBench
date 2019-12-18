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
 int NID_INVAL ; 
 int* pxm_to_node_map ; 

int pxm_to_node(int pxm)
{
	if (pxm < 0)
		return NID_INVAL;
	return pxm_to_node_map[pxm];
}