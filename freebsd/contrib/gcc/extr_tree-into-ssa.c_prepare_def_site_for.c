#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* basic_block ;
struct TYPE_5__ {scalar_t__ index; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSA_NAME_VERSION (int /*<<< orphan*/ ) ; 
 TYPE_1__* bb_for_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_bit_p (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ last_basic_block ; 
 int /*<<< orphan*/  mark_block_for_update (TYPE_1__*) ; 
 int /*<<< orphan*/  mark_def_interesting (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/ * names_to_release ; 

__attribute__((used)) static void
prepare_def_site_for (tree name, bool insert_phi_p)
{
  tree stmt;
  basic_block bb;

  gcc_assert (names_to_release == NULL
	      || !bitmap_bit_p (names_to_release, SSA_NAME_VERSION (name)));

  stmt = SSA_NAME_DEF_STMT (name);
  bb = bb_for_stmt (stmt);
  if (bb)
    {
      gcc_assert (bb->index < last_basic_block);
      mark_block_for_update (bb);
      mark_def_interesting (name, stmt, bb, insert_phi_p);
    }
}