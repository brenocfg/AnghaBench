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
struct lcs_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 struct lcs_buffer* __lcs_get_buffer (struct lcs_channel*) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static struct lcs_buffer *
lcs_get_buffer(struct lcs_channel *channel)
{
	struct lcs_buffer *buffer;
	unsigned long flags;

	LCS_DBF_TEXT(5, trace, "getbuff");
	spin_lock_irqsave(get_ccwdev_lock(channel->ccwdev), flags);
	buffer = __lcs_get_buffer(channel);
	spin_unlock_irqrestore(get_ccwdev_lock(channel->ccwdev), flags);
	return buffer;
}