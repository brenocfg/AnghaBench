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
struct iscsi_cls_session {unsigned int target_id; int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 struct iscsi_cls_session* iscsi_dev_to_session (struct device*) ; 
 int /*<<< orphan*/  iscsi_is_session_dev (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int iscsi_get_next_target_id(struct device *dev, void *data)
{
	struct iscsi_cls_session *session;
	unsigned long flags;
	int err = 0;

	if (!iscsi_is_session_dev(dev))
		return 0;

	session = iscsi_dev_to_session(dev);
	spin_lock_irqsave(&session->lock, flags);
	if (*((unsigned int *) data) == session->target_id)
		err = -EEXIST;
	spin_unlock_irqrestore(&session->lock, flags);
	return err;
}