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
struct metapage {int /*<<< orphan*/  page; int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  META_io ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_on_page_writeback (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void metapage_wait_for_io(struct metapage *mp)
{
	if (test_bit(META_io, &mp->flag))
		wait_on_page_writeback(mp->page);
}