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
typedef  TYPE_1__* tree_live_info_p ;
typedef  int /*<<< orphan*/  bitmap ;
struct TYPE_3__ {int /*<<< orphan*/ * livein; } ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bitmap
live_entry_blocks (tree_live_info_p live, int p)
{
  gcc_assert (live->livein);
  return live->livein[p];
}