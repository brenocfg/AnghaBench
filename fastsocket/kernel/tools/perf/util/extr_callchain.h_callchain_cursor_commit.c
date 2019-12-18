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
struct callchain_cursor {scalar_t__ pos; int /*<<< orphan*/  first; int /*<<< orphan*/  curr; } ;

/* Variables and functions */

__attribute__((used)) static inline void callchain_cursor_commit(struct callchain_cursor *cursor)
{
	cursor->curr = cursor->first;
	cursor->pos = 0;
}