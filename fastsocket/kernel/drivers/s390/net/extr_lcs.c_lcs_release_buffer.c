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
struct lcs_channel {int /*<<< orphan*/  ccwdev; } ;
struct lcs_buffer {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ LCS_BUF_STATE_EMPTY ; 
 scalar_t__ LCS_BUF_STATE_LOCKED ; 
 scalar_t__ LCS_BUF_STATE_PROCESSED ; 
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static void
lcs_release_buffer(struct lcs_channel *channel, struct lcs_buffer *buffer)
{
	unsigned long flags;

	LCS_DBF_TEXT(5, trace, "relbuff");
	BUG_ON(buffer->state != LCS_BUF_STATE_LOCKED &&
	       buffer->state != LCS_BUF_STATE_PROCESSED);
	spin_lock_irqsave(get_ccwdev_lock(channel->ccwdev), flags);
	buffer->state = LCS_BUF_STATE_EMPTY;
	spin_unlock_irqrestore(get_ccwdev_lock(channel->ccwdev), flags);
}