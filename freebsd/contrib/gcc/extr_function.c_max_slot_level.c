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
 int VEC_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  temp_slot_p ; 
 int /*<<< orphan*/  used_temp_slots ; 

__attribute__((used)) static int
max_slot_level (void)
{
  if (!used_temp_slots)
    return -1;

  return VEC_length (temp_slot_p, used_temp_slots) - 1;
}