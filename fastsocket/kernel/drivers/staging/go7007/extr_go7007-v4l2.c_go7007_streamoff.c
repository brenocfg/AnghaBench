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
struct go7007 {int /*<<< orphan*/  hw_lock; int /*<<< orphan*/  spinlock; scalar_t__ streaming; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  abort_queued (struct go7007*) ; 
 int /*<<< orphan*/  go7007_reset_encoder (struct go7007*) ; 
 int /*<<< orphan*/  go7007_stream_stop (struct go7007*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int go7007_streamoff(struct go7007 *go)
{
	int retval = -EINVAL;
	unsigned long flags;

	mutex_lock(&go->hw_lock);
	if (go->streaming) {
		go->streaming = 0;
		go7007_stream_stop(go);
		spin_lock_irqsave(&go->spinlock, flags);
		abort_queued(go);
		spin_unlock_irqrestore(&go->spinlock, flags);
		go7007_reset_encoder(go);
		retval = 0;
	}
	mutex_unlock(&go->hw_lock);
	return 0;
}