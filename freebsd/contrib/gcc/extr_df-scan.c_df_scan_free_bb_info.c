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
struct df_scan_bb_info {int dummy; } ;
struct dataflow {int /*<<< orphan*/  block_pool; } ;
typedef  TYPE_1__* basic_block ;
struct TYPE_3__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  df_bb_refs_delete (struct dataflow*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pool_free (int /*<<< orphan*/ ,struct df_scan_bb_info*) ; 

__attribute__((used)) static void
df_scan_free_bb_info (struct dataflow *dflow, basic_block bb, void *vbb_info)
{
  struct df_scan_bb_info *bb_info = (struct df_scan_bb_info *) vbb_info;
  if (bb_info)
    {
      df_bb_refs_delete (dflow, bb->index);
      pool_free (dflow->block_pool, bb_info);
    }
}