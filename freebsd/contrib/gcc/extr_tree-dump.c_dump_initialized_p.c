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
struct dump_file_info {scalar_t__ state; } ;
typedef  enum tree_dump_index { ____Placeholder_tree_dump_index } tree_dump_index ;

/* Variables and functions */
 struct dump_file_info* get_dump_file_info (int) ; 

int
dump_initialized_p (enum tree_dump_index phase)
{
  struct dump_file_info *dfi = get_dump_file_info (phase);
  return dfi->state > 0;
}