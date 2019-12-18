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
struct machine_function {int /*<<< orphan*/  func_type; } ;
typedef  struct machine_function machine_function ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_FT_UNKNOWN ; 
 scalar_t__ ggc_alloc_cleared (int) ; 

__attribute__((used)) static struct machine_function *
arm_init_machine_status (void)
{
  struct machine_function *machine;
  machine = (machine_function *) ggc_alloc_cleared (sizeof (machine_function));

#if ARM_FT_UNKNOWN != 0
  machine->func_type = ARM_FT_UNKNOWN;
#endif
  return machine;
}