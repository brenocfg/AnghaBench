#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  overflow_flag_lock; scalar_t__ overflow_flag_lock_initialized; int /*<<< orphan*/  queue; int /*<<< orphan*/  avf; int /*<<< orphan*/  format_options; } ;
typedef  TYPE_1__ FifoContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_thread_message_queue_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avformat_free_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fifo_deinit(AVFormatContext *avf)
{
    FifoContext *fifo = avf->priv_data;

    av_dict_free(&fifo->format_options);
    avformat_free_context(fifo->avf);
    av_thread_message_queue_free(&fifo->queue);
    if (fifo->overflow_flag_lock_initialized)
        pthread_mutex_destroy(&fifo->overflow_flag_lock);
}