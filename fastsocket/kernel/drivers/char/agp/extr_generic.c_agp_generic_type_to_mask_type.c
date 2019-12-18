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
struct agp_bridge_data {int dummy; } ;

/* Variables and functions */
 int AGP_USER_TYPES ; 

int agp_generic_type_to_mask_type(struct agp_bridge_data *bridge,
				  int type)
{
	if (type >= AGP_USER_TYPES)
		return 0;
	return type;
}