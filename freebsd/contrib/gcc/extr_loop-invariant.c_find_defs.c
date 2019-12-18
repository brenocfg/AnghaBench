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
struct loop {unsigned int num_nodes; } ;
typedef  int /*<<< orphan*/  bitmap ;
typedef  TYPE_1__* basic_block ;
struct TYPE_3__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BITMAP_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  df ; 
 int /*<<< orphan*/  df_analyze (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  df_set_blocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
find_defs (struct loop *loop, basic_block *body)
{
  unsigned i;
  bitmap blocks = BITMAP_ALLOC (NULL);

  for (i = 0; i < loop->num_nodes; i++)
    bitmap_set_bit (blocks, body[i]->index);

  df_set_blocks (df, blocks);
  df_analyze (df);
  BITMAP_FREE (blocks);
}