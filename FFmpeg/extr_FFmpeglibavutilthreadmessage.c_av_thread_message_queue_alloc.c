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
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOSYS ; 

int av_thread_message_queue_alloc(AVThreadMessageQueue **mq,
                                  unsigned nelem,
                                  unsigned elsize)
{
#if HAVE_THREADS
    AVThreadMessageQueue *rmq;
    int ret = 0;

    if (nelem > INT_MAX / elsize)
        return AVERROR(EINVAL);
    if (!(rmq = av_mallocz(sizeof(*rmq))))
        return AVERROR(ENOMEM);
    if ((ret = pthread_mutex_init(&rmq->lock, NULL))) {
        av_free(rmq);
        return AVERROR(ret);
    }
    if ((ret = pthread_cond_init(&rmq->cond_recv, NULL))) {
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        return AVERROR(ret);
    }
    if ((ret = pthread_cond_init(&rmq->cond_send, NULL))) {
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        return AVERROR(ret);
    }
    if (!(rmq->fifo = av_fifo_alloc(elsize * nelem))) {
        pthread_cond_destroy(&rmq->cond_send);
        pthread_cond_destroy(&rmq->cond_recv);
        pthread_mutex_destroy(&rmq->lock);
        av_free(rmq);
        return AVERROR(ENOMEM);
    }
    rmq->elsize = elsize;
    *mq = rmq;
    return 0;
#else
    *mq = NULL;
    return AVERROR(ENOSYS);
#endif /* HAVE_THREADS */
}