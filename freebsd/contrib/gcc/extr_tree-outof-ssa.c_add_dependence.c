#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* value_expr_p ;
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_2__* temp_expr_table_p ;
struct TYPE_10__ {int /*<<< orphan*/  partition_in_use; int /*<<< orphan*/ * version_info; TYPE_1__** partition_dep_list; int /*<<< orphan*/  map; TYPE_1__* pending_dependence; int /*<<< orphan*/  replaceable; } ;
struct TYPE_9__ {int value; struct TYPE_9__* next; } ;

/* Variables and functions */
 int NO_PARTITION ; 
 int SSA_NAME_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_info_to_list (TYPE_2__*,TYPE_1__**,TYPE_1__*) ; 
 int /*<<< orphan*/  add_value_to_list (TYPE_2__*,TYPE_1__**,int) ; 
 scalar_t__ bitmap_bit_p (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int var_to_partition (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_dependence (temp_expr_table_p tab, int version, tree var)
{
  int i, x;
  value_expr_p info;

  i = SSA_NAME_VERSION (var);
  if (bitmap_bit_p (tab->replaceable, i))
    {
      /* This variable is being substituted, so use whatever dependences
         were queued up when we marked this as replaceable earlier.  */
      while ((info = tab->pending_dependence))
        {
	  tab->pending_dependence = info->next;
	  /* Get the partition this variable was dependent on. Reuse this
	     object to represent the current  expression instead.  */
	  x = info->value;
	  info->value = version;
	  add_info_to_list (tab, &(tab->partition_dep_list[x]), info);
          add_value_to_list (tab, 
			     (value_expr_p *)&(tab->version_info[version]), x);
	  bitmap_set_bit (tab->partition_in_use, x);
	}
    }
  else
    {
      i = var_to_partition (tab->map, var);
      gcc_assert (i != NO_PARTITION);
      add_value_to_list (tab, &(tab->partition_dep_list[i]), version);
      add_value_to_list (tab, 
			 (value_expr_p *)&(tab->version_info[version]), i);
      bitmap_set_bit (tab->partition_in_use, i);
    }
}