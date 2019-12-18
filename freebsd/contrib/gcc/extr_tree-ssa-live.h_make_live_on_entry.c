#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* tree_live_info_p ;
typedef  TYPE_2__* basic_block ;
struct TYPE_6__ {int index; } ;
struct TYPE_5__ {int /*<<< orphan*/  global; int /*<<< orphan*/ * livein; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void 
make_live_on_entry (tree_live_info_p live, basic_block bb , int p)
{
  bitmap_set_bit (live->livein[p], bb->index);
  bitmap_set_bit (live->global, p);
}