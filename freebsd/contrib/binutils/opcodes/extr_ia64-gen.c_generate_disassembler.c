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
struct main_entry {int /*<<< orphan*/  completers; int /*<<< orphan*/  main_index; TYPE_1__* opcode; } ;
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  mask; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 scalar_t__ IA64_TYPE_DYN ; 
 int /*<<< orphan*/  add_dis_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bittree ; 
 int /*<<< orphan*/  compact_distree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_distable () ; 
 int /*<<< orphan*/  gen_dis_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_bittree_entry () ; 
 struct main_entry** ordered_table ; 
 int otlen ; 
 int /*<<< orphan*/  print_dis_table () ; 

__attribute__((used)) static void
generate_disassembler (void)
{
  int i;

  bittree = make_bittree_entry ();

  for (i = 0; i < otlen; i++)
    {
      struct main_entry *ptr = ordered_table[i];

      if (ptr->opcode->type != IA64_TYPE_DYN)
	add_dis_entry (bittree,
		       ptr->opcode->opcode, ptr->opcode->mask, 
		       ptr->main_index,
		       ptr->completers, 1);
    }

  compact_distree (bittree);
  finish_distable ();
  gen_dis_table (bittree);

  print_dis_table ();
}