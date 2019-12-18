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
struct bdi_writeback {int /*<<< orphan*/  b_io; int /*<<< orphan*/  b_dirty; int /*<<< orphan*/  b_more_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  move_expired_inodes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long*) ; 

__attribute__((used)) static void queue_io(struct bdi_writeback *wb, unsigned long *older_than_this)
{
	list_splice_init(&wb->b_more_io, &wb->b_io);
	move_expired_inodes(&wb->b_dirty, &wb->b_io, older_than_this);
}