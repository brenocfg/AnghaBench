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
typedef  int /*<<< orphan*/  AVThreadMessageQueue ;

/* Variables and functions */

void av_thread_message_flush(AVThreadMessageQueue *mq)
{
#if HAVE_THREADS
    int used, off;
    void *free_func = mq->free_func;

    pthread_mutex_lock(&mq->lock);
    used = av_fifo_size(mq->fifo);
    if (free_func)
        for (off = 0; off < used; off += mq->elsize)
            av_fifo_generic_peek_at(mq->fifo, mq, off, mq->elsize, free_func_wrap);
    av_fifo_drain(mq->fifo, used);
    /* only the senders need to be notified since the queue is empty and there
     * is nothing to read */
    pthread_cond_broadcast(&mq->cond_send);
    pthread_mutex_unlock(&mq->lock);
#endif /* HAVE_THREADS */
}