#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* alt_state_t ;
struct TYPE_4__ {struct TYPE_4__* next_alt_state; } ;

/* Variables and functions */
 TYPE_1__* first_free_alt_state ; 

__attribute__((used)) static void
free_alt_state (alt_state_t alt_state)
{
  if (alt_state == NULL)
    return;
  alt_state->next_alt_state = first_free_alt_state;
  first_free_alt_state = alt_state;
}