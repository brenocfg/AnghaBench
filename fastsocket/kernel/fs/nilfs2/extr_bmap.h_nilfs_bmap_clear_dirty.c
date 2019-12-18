#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nilfs_bmap {int /*<<< orphan*/  b_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NILFS_BMAP_DIRTY ; 

__attribute__((used)) static inline void nilfs_bmap_clear_dirty(struct nilfs_bmap *bmap)
{
	bmap->b_state &= ~NILFS_BMAP_DIRTY;
}