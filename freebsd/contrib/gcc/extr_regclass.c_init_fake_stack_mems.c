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
 int MAX_MACHINE_MODE ; 
 int /*<<< orphan*/  gen_rtx_MEM (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_pointer_rtx ; 
 int /*<<< orphan*/ * top_of_stack ; 

void
init_fake_stack_mems (void)
{
  {
    int i;

    for (i = 0; i < MAX_MACHINE_MODE; i++)
      top_of_stack[i] = gen_rtx_MEM (i, stack_pointer_rtx);
  }
}