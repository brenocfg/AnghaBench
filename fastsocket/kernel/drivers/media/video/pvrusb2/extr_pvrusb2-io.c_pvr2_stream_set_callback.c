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
struct pvr2_stream {int /*<<< orphan*/  mutex; int /*<<< orphan*/  list_lock; int /*<<< orphan*/  callback_func; void* callback_data; } ;
typedef  int /*<<< orphan*/  pvr2_stream_callback ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void pvr2_stream_set_callback(struct pvr2_stream *sp,
			      pvr2_stream_callback func,
			      void *data)
{
	unsigned long irq_flags;
	mutex_lock(&sp->mutex); do {
		spin_lock_irqsave(&sp->list_lock,irq_flags);
		sp->callback_data = data;
		sp->callback_func = func;
		spin_unlock_irqrestore(&sp->list_lock,irq_flags);
	} while(0); mutex_unlock(&sp->mutex);
}