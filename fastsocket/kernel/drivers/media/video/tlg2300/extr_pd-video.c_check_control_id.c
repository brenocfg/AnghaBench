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
struct TYPE_2__ {scalar_t__ id; } ;
struct poseidon_control {TYPE_1__ v4l2_ctrl; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int ARRAY_SIZE (struct poseidon_control*) ; 
 struct poseidon_control* controls ; 

__attribute__((used)) static struct poseidon_control *check_control_id(__u32 id)
{
	struct poseidon_control *control = &controls[0];
	int array_size = ARRAY_SIZE(controls);

	for (; control < &controls[array_size]; control++)
		if (control->v4l2_ctrl.id  == id)
			return control;
	return NULL;
}