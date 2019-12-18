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
typedef  int /*<<< orphan*/  arc_t ;
struct TYPE_3__ {int /*<<< orphan*/  first_out_arc; } ;

/* Variables and functions */

__attribute__((used)) static arc_t
first_out_arc (state_t state)
{
  return state->first_out_arc;
}