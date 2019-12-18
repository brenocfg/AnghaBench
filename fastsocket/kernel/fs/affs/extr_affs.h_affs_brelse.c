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
struct buffer_head {scalar_t__ b_blocknr; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  pr_debug (char*,long long) ; 

__attribute__((used)) static inline void
affs_brelse(struct buffer_head *bh)
{
	if (bh)
		pr_debug("affs_brelse: %lld\n", (long long) bh->b_blocknr);
	brelse(bh);
}