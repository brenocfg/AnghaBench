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
struct xfs_btree_block {int /*<<< orphan*/  bb_numrecs; } ;
typedef  int /*<<< orphan*/  __uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void xfs_btree_set_numrecs(struct xfs_btree_block *block,
		__uint16_t numrecs)
{
	block->bb_numrecs = cpu_to_be16(numrecs);
}