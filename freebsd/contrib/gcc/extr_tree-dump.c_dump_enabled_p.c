#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dump_file_info {int state; } ;
typedef  enum tree_dump_index { ____Placeholder_tree_dump_index } tree_dump_index ;
struct TYPE_4__ {scalar_t__ state; } ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ TDI_end ; 
 int TDI_none ; 
 int TDI_tree_all ; 
 TYPE_2__* dump_files ; 
 TYPE_1__* extra_dump_files ; 
 size_t extra_dump_files_in_use ; 
 struct dump_file_info* get_dump_file_info (int) ; 

int
dump_enabled_p (enum tree_dump_index phase)
{
  if (phase == TDI_tree_all)
    {
      size_t i;
      for (i = TDI_none + 1; i < (size_t) TDI_end; i++)
	if (dump_files[i].state)
	  return 1;
      for (i = 0; i < extra_dump_files_in_use; i++)
	if (extra_dump_files[i].state)
	  return 1;
      return 0;
    }
  else
    {
      struct dump_file_info *dfi = get_dump_file_info (phase);
      return dfi->state;
    }
}