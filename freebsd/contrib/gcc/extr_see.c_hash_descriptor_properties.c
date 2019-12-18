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
struct see_register_properties {int /*<<< orphan*/  regno; } ;
typedef  int /*<<< orphan*/  hashval_t ;

/* Variables and functions */

__attribute__((used)) static hashval_t
hash_descriptor_properties (const void *p)
{
  const struct see_register_properties *curr_prop = p;
  return curr_prop->regno;
}