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
struct pending_request {struct file_info* file_info; } ;
struct file_info {int /*<<< orphan*/  reqlists_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __queue_complete_req (struct pending_request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void queue_complete_req(struct pending_request *req)
{
	unsigned long flags;
	struct file_info *fi = req->file_info;

	spin_lock_irqsave(&fi->reqlists_lock, flags);
	__queue_complete_req(req);
	spin_unlock_irqrestore(&fi->reqlists_lock, flags);
}