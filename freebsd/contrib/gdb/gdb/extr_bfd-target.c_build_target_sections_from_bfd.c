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
struct target_ops {struct section_table* to_sections; } ;
struct section_table {int dummy; } ;
struct section_closure {struct section_table* end; } ;
struct bfd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_to_section_table ; 
 unsigned int bfd_count_sections (struct bfd*) ; 
 int /*<<< orphan*/  bfd_map_over_sections (struct bfd*,int /*<<< orphan*/ ,struct section_closure*) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  target_resize_to_sections (struct target_ops*,unsigned int) ; 

void
build_target_sections_from_bfd (struct target_ops *targ, struct bfd *abfd)
{
  unsigned count;
  struct section_table *start;
  struct section_closure cl;

  count = bfd_count_sections (abfd);
  target_resize_to_sections (targ, count);
  start = targ->to_sections;
  cl.end = targ->to_sections;
  bfd_map_over_sections (abfd, add_to_section_table, &cl);
  gdb_assert (cl.end - start <= count);
}