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
typedef  TYPE_1__* basic_block ;
struct TYPE_3__ {scalar_t__ loop_father; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__* BASIC_BLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUM_FIXED_BLOCKS ; 
 int /*<<< orphan*/  print_loop (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

void
print_loop_ir (FILE *file)
{
  basic_block bb;

  bb = BASIC_BLOCK (NUM_FIXED_BLOCKS);
  if (bb && bb->loop_father)
    print_loop (file, bb->loop_father, 0);
}