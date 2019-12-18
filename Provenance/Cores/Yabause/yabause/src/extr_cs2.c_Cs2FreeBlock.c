#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int size; } ;
typedef  TYPE_2__ block_struct ;
struct TYPE_5__ {int /*<<< orphan*/  HIRQ; } ;
struct TYPE_7__ {TYPE_1__ reg; scalar_t__ isbufferfull; int /*<<< orphan*/  blockfreespace; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDB_HIRQ_BFUL ; 
 TYPE_4__* Cs2Area ; 

void Cs2FreeBlock(block_struct * blk) {
  if (blk == NULL) return;
  blk->size = -1;
  Cs2Area->blockfreespace++;
  Cs2Area->isbufferfull = 0;
  Cs2Area->reg.HIRQ &= ~CDB_HIRQ_BFUL;
}