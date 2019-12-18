#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * container; int /*<<< orphan*/ * ptr; } ;
struct TYPE_6__ {TYPE_2__* bb; TYPE_3__ tsi; } ;
typedef  TYPE_1__ block_stmt_iterator ;
typedef  TYPE_2__* basic_block ;
struct TYPE_7__ {scalar_t__ index; scalar_t__ stmt_list; } ;

/* Variables and functions */
 scalar_t__ NUM_FIXED_BLOCKS ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_3__ tsi_start (scalar_t__) ; 

__attribute__((used)) static inline block_stmt_iterator
bsi_start (basic_block bb)
{
  block_stmt_iterator bsi;
  if (bb->stmt_list)
    bsi.tsi = tsi_start (bb->stmt_list);
  else
    {
      gcc_assert (bb->index < NUM_FIXED_BLOCKS);
      bsi.tsi.ptr = NULL;
      bsi.tsi.container = NULL;
    }
  bsi.bb = bb;
  return bsi;
}