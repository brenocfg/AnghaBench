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
struct uvc_video_queue {int type; int /*<<< orphan*/  flags; int /*<<< orphan*/  irqqueue; int /*<<< orphan*/  mainqueue; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  mutex; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UVC_QUEUE_DROP_CORRUPTED ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void uvc_queue_init(struct uvc_video_queue *queue, enum v4l2_buf_type type,
		    int drop_corrupted)
{
	mutex_init(&queue->mutex);
	spin_lock_init(&queue->irqlock);
	INIT_LIST_HEAD(&queue->mainqueue);
	INIT_LIST_HEAD(&queue->irqqueue);
	queue->flags = drop_corrupted ? UVC_QUEUE_DROP_CORRUPTED : 0;
	queue->type = type;
}