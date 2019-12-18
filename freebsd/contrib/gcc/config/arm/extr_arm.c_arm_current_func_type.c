#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* machine; } ;
struct TYPE_3__ {unsigned long func_type; } ;

/* Variables and functions */
 scalar_t__ ARM_FT_UNKNOWN ; 
 scalar_t__ ARM_FUNC_TYPE (unsigned long) ; 
 unsigned long arm_compute_func_type () ; 
 TYPE_2__* cfun ; 

unsigned long
arm_current_func_type (void)
{
  if (ARM_FUNC_TYPE (cfun->machine->func_type) == ARM_FT_UNKNOWN)
    cfun->machine->func_type = arm_compute_func_type ();

  return cfun->machine->func_type;
}