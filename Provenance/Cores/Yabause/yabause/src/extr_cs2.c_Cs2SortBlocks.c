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
struct TYPE_3__ {int /*<<< orphan*/ ** block; } ;
typedef  TYPE_1__ partition_struct ;

/* Variables and functions */
 unsigned int MAX_BLOCKS ; 

void Cs2SortBlocks(partition_struct * part) {
  unsigned int from, to;

  for (from = to = 0; from < MAX_BLOCKS; from++)
  {
     if (part->block[from] != NULL)
     {
        if (to != from)
        {
           part->block[to] = part->block[from];
        }
        to++;
     }
  }

  for (; to < MAX_BLOCKS; to++) {
      part->block[to] = NULL;
  }
}