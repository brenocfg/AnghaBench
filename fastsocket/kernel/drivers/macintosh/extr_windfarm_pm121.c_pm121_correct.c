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
struct pm121_correction {int slope; scalar_t__ offset; } ;
typedef  int s32 ;

/* Variables and functions */
 int average_power ; 
 struct pm121_correction** corrections ; 
 int max (int,int) ; 
 int pm121_mach_model ; 

__attribute__((used)) static s32 pm121_correct(s32 new_setpoint,
			 unsigned int control_id,
			 s32 min)
{
	s32 new_min;
	struct pm121_correction *correction;
	correction = &corrections[control_id][pm121_mach_model - 2];

	new_min = (average_power * correction->slope) >> 16;
	new_min += correction->offset;
	new_min = (new_min >> 16) + min;

	return max(new_setpoint, max(new_min, 0));
}