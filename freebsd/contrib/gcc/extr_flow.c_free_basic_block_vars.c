#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* rtl; } ;
struct TYPE_12__ {TYPE_4__ il; int /*<<< orphan*/ * aux; } ;
struct TYPE_8__ {TYPE_1__* rtl; } ;
struct TYPE_11__ {TYPE_2__ il; int /*<<< orphan*/ * aux; } ;
struct TYPE_9__ {int /*<<< orphan*/ * global_live_at_end; } ;
struct TYPE_7__ {int /*<<< orphan*/ * global_live_at_start; } ;

/* Variables and functions */
 TYPE_6__* ENTRY_BLOCK_PTR ; 
 TYPE_5__* EXIT_BLOCK_PTR ; 
 int /*<<< orphan*/ * basic_block_info ; 
 int /*<<< orphan*/  clear_edges () ; 
 int /*<<< orphan*/ * label_to_block_map ; 
 scalar_t__ last_basic_block ; 
 scalar_t__ n_basic_blocks ; 
 scalar_t__ n_edges ; 

void
free_basic_block_vars (void)
{
  if (basic_block_info)
    {
      clear_edges ();
      basic_block_info = NULL;
    }
  n_basic_blocks = 0;
  last_basic_block = 0;
  n_edges = 0;

  label_to_block_map = NULL;

  ENTRY_BLOCK_PTR->aux = NULL;
  ENTRY_BLOCK_PTR->il.rtl->global_live_at_end = NULL;
  EXIT_BLOCK_PTR->aux = NULL;
  EXIT_BLOCK_PTR->il.rtl->global_live_at_start = NULL;
}