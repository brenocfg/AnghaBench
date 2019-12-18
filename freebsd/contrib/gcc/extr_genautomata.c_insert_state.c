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
typedef  scalar_t__ state_t ;

/* Variables and functions */
 void** htab_find_slot (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  state_table ; 

__attribute__((used)) static state_t
insert_state (state_t state)
{
  void **entry_ptr;

  entry_ptr = htab_find_slot (state_table, (void *) state, 1);
  if (*entry_ptr == NULL)
    *entry_ptr = (void *) state;
  return (state_t) *entry_ptr;
}