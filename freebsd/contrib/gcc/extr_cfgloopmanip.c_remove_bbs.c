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
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  delete_basic_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_bb_from_loops (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
remove_bbs (basic_block *bbs, int nbbs)
{
  int i;

  for (i = 0; i < nbbs; i++)
    {
      remove_bb_from_loops (bbs[i]);
      delete_basic_block (bbs[i]);
    }
}