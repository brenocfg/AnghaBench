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
struct machine_function {int dummy; } ;

/* Variables and functions */
 scalar_t__ ggc_alloc_cleared (int) ; 

__attribute__((used)) static struct machine_function *
mips_init_machine_status (void)
{
  return ((struct machine_function *)
	  ggc_alloc_cleared (sizeof (struct machine_function)));
}