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
struct value {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * bound_name ; 
 struct value* value_struct_elt (struct value**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static struct value *
desc_one_bound (struct value *bounds, int i, int which)
{
  return value_struct_elt (&bounds, NULL, bound_name[2 * i + which - 2], NULL,
			   "Bad GNAT array descriptor bounds");
}