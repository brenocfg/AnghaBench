#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ n_elems; } ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_code_hoist_mem (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  alloc_hash_table (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compute_code_hoist_data () ; 
 int /*<<< orphan*/  compute_hash_table (TYPE_1__*) ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  dump_hash_table (scalar_t__,char*,TYPE_1__*) ; 
 TYPE_1__ expr_hash_table ; 
 int /*<<< orphan*/  free_code_hoist_mem () ; 
 int /*<<< orphan*/  free_hash_table (TYPE_1__*) ; 
 int /*<<< orphan*/  hoist_code () ; 
 int /*<<< orphan*/  last_basic_block ; 
 int /*<<< orphan*/  max_cuid ; 

__attribute__((used)) static int
one_code_hoisting_pass (void)
{
  int changed = 0;

  alloc_hash_table (max_cuid, &expr_hash_table, 0);
  compute_hash_table (&expr_hash_table);
  if (dump_file)
    dump_hash_table (dump_file, "Code Hosting Expressions", &expr_hash_table);

  if (expr_hash_table.n_elems > 0)
    {
      alloc_code_hoist_mem (last_basic_block, expr_hash_table.n_elems);
      compute_code_hoist_data ();
      hoist_code ();
      free_code_hoist_mem ();
    }

  free_hash_table (&expr_hash_table);

  return changed;
}