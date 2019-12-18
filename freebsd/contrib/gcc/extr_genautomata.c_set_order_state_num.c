#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* state_t ;
struct TYPE_3__ {int /*<<< orphan*/  order_state_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  curr_state_order_num ; 

__attribute__((used)) static void
set_order_state_num (state_t state)
{
  state->order_state_num = curr_state_order_num;
  curr_state_order_num++;
}