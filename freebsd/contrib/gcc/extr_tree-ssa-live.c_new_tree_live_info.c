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
typedef  int /*<<< orphan*/  var_map ;
typedef  TYPE_1__* tree_live_info_p ;
struct tree_live_info_d {int dummy; } ;
typedef  void* bitmap ;
struct TYPE_3__ {int /*<<< orphan*/ * liveout; void** livein; void* global; int /*<<< orphan*/  num_blocks; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 void* BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  last_basic_block ; 
 unsigned int num_var_partitions (int /*<<< orphan*/ ) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static tree_live_info_p
new_tree_live_info (var_map map)
{
  tree_live_info_p live;
  unsigned x;

  live = (tree_live_info_p) xmalloc (sizeof (struct tree_live_info_d));
  live->map = map;
  live->num_blocks = last_basic_block;

  live->global = BITMAP_ALLOC (NULL);

  live->livein = (bitmap *)xmalloc (num_var_partitions (map) * sizeof (bitmap));
  for (x = 0; x < num_var_partitions (map); x++)
    live->livein[x] = BITMAP_ALLOC (NULL);

  /* liveout is deferred until it is actually requested.  */
  live->liveout = NULL;
  return live;
}