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
struct TYPE_2__ {int (* switch_layer ) (int,int) ;} ;

/* Variables and functions */
 TYPE_1__ plat_target ; 
 int stub1 (int,int) ; 

__attribute__((used)) static __inline int plat_target_switch_layer(int which, int enable)
{
	if (plat_target.switch_layer)
		return plat_target.switch_layer(which, enable);
	return -1;
}