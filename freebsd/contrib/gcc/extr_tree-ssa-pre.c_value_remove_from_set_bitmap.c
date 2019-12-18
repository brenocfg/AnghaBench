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
typedef  TYPE_1__* value_set_t ;
typedef  int /*<<< orphan*/  tree ;
struct TYPE_3__ {int /*<<< orphan*/  values; int /*<<< orphan*/  indexed; } ;

/* Variables and functions */
 int /*<<< orphan*/  VALUE_HANDLE_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
value_remove_from_set_bitmap (value_set_t set, tree v)
{
  gcc_assert (set->indexed);

  if (!set->values)
    return;

  bitmap_clear_bit (set->values, VALUE_HANDLE_ID (v));
}