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
typedef  TYPE_2__* alt_state_t ;
struct TYPE_4__ {TYPE_1__* state; } ;
struct TYPE_3__ {scalar_t__ unique_num; } ;

/* Variables and functions */

__attribute__((used)) static int
alt_state_cmp (const void *alt_state_ptr_1, const void *alt_state_ptr_2)
{
  if ((*(alt_state_t *) alt_state_ptr_1)->state->unique_num
      == (*(alt_state_t *) alt_state_ptr_2)->state->unique_num)
    return 0;
  else if ((*(alt_state_t *) alt_state_ptr_1)->state->unique_num
	   < (*(alt_state_t *) alt_state_ptr_2)->state->unique_num)
    return -1;
  else
    return 1;
}