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
struct receiver_data {int workload; int /*<<< orphan*/  queue; int /*<<< orphan*/  id; } ;
struct message {scalar_t__ magic; TYPE_2__* frame; } ;
struct TYPE_5__ {int /*<<< orphan*/ * metadata; } ;
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 scalar_t__ MAGIC ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 TYPE_1__* av_dict_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  av_thread_message_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_thread_message_queue_nb_elems (int /*<<< orphan*/ ) ; 
 int av_thread_message_queue_recv (int /*<<< orphan*/ ,struct message*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_thread_message_queue_set_err_send (int /*<<< orphan*/ ,int) ; 
 int rand () ; 

__attribute__((used)) static void *receiver_thread(void *arg)
{
    int i, ret = 0;
    struct receiver_data *rd = arg;

    for (i = 0; i < rd->workload; i++) {
        if (rand() % rd->workload < rd->workload / 10) {
            av_log(NULL, AV_LOG_INFO, "receiver #%d: flushing the queue, "
                   "discarding %d message(s)\n", rd->id,
                   av_thread_message_queue_nb_elems(rd->queue));
            av_thread_message_flush(rd->queue);
        } else {
            struct message msg;
            AVDictionary *meta;
            AVDictionaryEntry *e;

            ret = av_thread_message_queue_recv(rd->queue, &msg, 0);
            if (ret < 0)
                break;
            av_assert0(msg.magic == MAGIC);
            meta = msg.frame->metadata;
            e = av_dict_get(meta, "sig", NULL, 0);
            av_log(NULL, AV_LOG_INFO, "got \"%s\" (%p)\n", e->value, msg.frame);
            av_frame_free(&msg.frame);
        }
    }

    av_log(NULL, AV_LOG_INFO, "consumed enough (%d), stop\n", i);
    av_thread_message_queue_set_err_send(rd->queue, ret < 0 ? ret : AVERROR_EOF);

    return NULL;
}