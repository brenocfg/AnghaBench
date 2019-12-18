#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* value_expr_p ;
typedef  TYPE_2__* temp_expr_table_p ;
struct TYPE_6__ {int /*<<< orphan*/  partition_in_use; TYPE_1__** partition_dep_list; } ;
struct TYPE_5__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_clear_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  finish_expr (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
kill_expr (temp_expr_table_p tab, int partition, bool clear_bit)
{
  value_expr_p ptr;

  /* Mark every active expr dependent on this var as not replaceable.  */
  while ((ptr = tab->partition_dep_list[partition]) != NULL)
    finish_expr (tab, ptr->value, false);

  if (clear_bit)
    bitmap_clear_bit (tab->partition_in_use, partition);
}