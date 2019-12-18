#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ifnet_t ;
typedef  int ifnet_offload_t ;
struct TYPE_3__ {int if_hwassist; } ;

/* Variables and functions */
 int offload_mask ; 

ifnet_offload_t
ifnet_offload(ifnet_t interface)
{
	return ((interface == NULL) ?
	    0 : (interface->if_hwassist & offload_mask));
}