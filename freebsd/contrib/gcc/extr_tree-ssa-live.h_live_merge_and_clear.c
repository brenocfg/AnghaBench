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
struct TYPE_3__ {int /*<<< orphan*/ * livein; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_ior_into (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void 
live_merge_and_clear (tree_live_info_p live, int p1, int p2)
{
  bitmap_ior_into (live->livein[p1], live->livein[p2]);
  bitmap_zero (live->livein[p2]);
}