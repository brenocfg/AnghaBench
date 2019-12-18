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
struct TYPE_3__ {int /*<<< orphan*/  reservs; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_unit_reserv (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
set_state_reserv (state_t state, int cycle_num, int unit_num)
{
  set_unit_reserv (state->reservs, cycle_num, unit_num);
}