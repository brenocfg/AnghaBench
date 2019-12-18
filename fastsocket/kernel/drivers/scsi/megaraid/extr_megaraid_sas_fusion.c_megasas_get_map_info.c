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
typedef  int u8 ;
struct megasas_instance {struct fusion_context* ctrl_context; } ;
struct fusion_context {int fast_path_io; } ;

/* Variables and functions */
 scalar_t__ MR_ValidateMapInfo (struct megasas_instance*) ; 
 int /*<<< orphan*/  megasas_get_ld_map_info (struct megasas_instance*) ; 

u8
megasas_get_map_info(struct megasas_instance *instance)
{
	struct fusion_context *fusion = instance->ctrl_context;

	fusion->fast_path_io = 0;
	if (!megasas_get_ld_map_info(instance)) {
		if (MR_ValidateMapInfo(instance)) {
			fusion->fast_path_io = 1;
			return 0;
		}
	}
	return 1;
}