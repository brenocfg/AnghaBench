#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {int write_trailer_ret; int /*<<< orphan*/  writer_thread; int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ FifoContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int) ; 
 int /*<<< orphan*/  AVERROR_EOF ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_thread_message_queue_set_err_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fifo_write_trailer(AVFormatContext *avf)
{
    FifoContext *fifo= avf->priv_data;
    int ret;

    av_thread_message_queue_set_err_recv(fifo->queue, AVERROR_EOF);

    ret = pthread_join(fifo->writer_thread, NULL);
    if (ret < 0) {
        av_log(avf, AV_LOG_ERROR, "pthread join error: %s\n",
               av_err2str(AVERROR(ret)));
        return AVERROR(ret);
    }

    ret = fifo->write_trailer_ret;
    return ret;
}