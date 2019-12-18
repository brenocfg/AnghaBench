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
struct see_register_properties {scalar_t__ regno; } ;

/* Variables and functions */

__attribute__((used)) static int
eq_descriptor_properties (const void *p1, const void *p2)
{
  const struct see_register_properties *curr_prop1 = p1;
  const struct see_register_properties *curr_prop2 = p2;

  return curr_prop1->regno == curr_prop2->regno;
}