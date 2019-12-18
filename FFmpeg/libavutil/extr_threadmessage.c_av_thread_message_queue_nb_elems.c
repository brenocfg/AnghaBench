#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int elsize; int /*<<< orphan*/  lock; int /*<<< orphan*/  fifo; } ;
typedef  TYPE_1__ AVThreadMessageQueue ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOSYS ; 
 int av_fifo_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int av_thread_message_queue_nb_elems(AVThreadMessageQueue *mq)
{
#if HAVE_THREADS
    int ret;
    pthread_mutex_lock(&mq->lock);
    ret = av_fifo_size(mq->fifo);
    pthread_mutex_unlock(&mq->lock);
    return ret / mq->elsize;
#else
    return AVERROR(ENOSYS);
#endif
}