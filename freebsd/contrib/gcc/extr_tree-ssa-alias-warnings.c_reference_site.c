#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_2__ {int /*<<< orphan*/  objs; int /*<<< orphan*/  ptrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  match (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* reference_table (int) ; 

__attribute__((used)) static tree
reference_site (tree object, bool is_ptr)
{
  if (is_ptr)
    return match (reference_table (true)->ptrs, object);
  else
    return match (reference_table (true)->objs, object);
}