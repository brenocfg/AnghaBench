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
struct b3dfg_dev {unsigned long cstate_tstamp; int /*<<< orphan*/  buffer_lock; int /*<<< orphan*/  cstate_lock; int /*<<< orphan*/  transmission_enabled; } ;
struct b3dfg_buffer {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ B3DFG_BUFFER_POPULATED ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int is_event_ready(struct b3dfg_dev *fgdev, struct b3dfg_buffer *buf,
			  unsigned long when)
{
	int result;
	unsigned long flags;

	spin_lock_irqsave(&fgdev->buffer_lock, flags);
	spin_lock(&fgdev->cstate_lock);
	result = (!fgdev->transmission_enabled ||
		  buf->state == B3DFG_BUFFER_POPULATED ||
		  when != fgdev->cstate_tstamp);
	spin_unlock(&fgdev->cstate_lock);
	spin_unlock_irqrestore(&fgdev->buffer_lock, flags);

	return result;
}