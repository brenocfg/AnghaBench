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
struct page {int dummy; } ;
struct loop_device {int (* transfer ) (struct loop_device*,int,struct page*,unsigned int,struct page*,unsigned int,int,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int stub1 (struct loop_device*,int,struct page*,unsigned int,struct page*,unsigned int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int
lo_do_transfer(struct loop_device *lo, int cmd,
	       struct page *rpage, unsigned roffs,
	       struct page *lpage, unsigned loffs,
	       int size, sector_t rblock)
{
	if (unlikely(!lo->transfer))
		return 0;

	return lo->transfer(lo, cmd, rpage, roffs, lpage, loffs, size, rblock);
}