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
struct xfs_ail_cursor {struct xfs_ail_cursor* next; int /*<<< orphan*/ * item; } ;
struct xfs_ail {struct xfs_ail_cursor xa_cursors; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct xfs_ail_cursor*) ; 

void
xfs_trans_ail_cursor_done(
	struct xfs_ail		*ailp,
	struct xfs_ail_cursor	*done)
{
	struct xfs_ail_cursor	*prev = NULL;
	struct xfs_ail_cursor	*cur;

	done->item = NULL;
	if (done == &ailp->xa_cursors)
		return;
	prev = &ailp->xa_cursors;
	for (cur = prev->next; cur; prev = cur, cur = prev->next) {
		if (cur == done) {
			prev->next = cur->next;
			break;
		}
	}
	ASSERT(cur);
}