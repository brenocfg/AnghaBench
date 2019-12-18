#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sender_data {int workload; int /*<<< orphan*/  queue; int /*<<< orphan*/  id; } ;
struct message {TYPE_1__* frame; int /*<<< orphan*/  magic; } ;
struct TYPE_4__ {int width; int height; int /*<<< orphan*/  format; int /*<<< orphan*/ * metadata; } ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_DICT_DONT_STRDUP_VAL ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  AV_PIX_FMT_RGBA ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  MAGIC ; 
 char* av_asprintf (char*,int,int,int /*<<< orphan*/ ) ; 
 int av_dict_set (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 
 int av_err2str (int) ; 
 TYPE_1__* av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (TYPE_1__**) ; 
 int av_frame_get_buffer (TYPE_1__*,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  av_thread_message_flush (int /*<<< orphan*/ ) ; 
 int av_thread_message_queue_send (int /*<<< orphan*/ ,struct message*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_thread_message_queue_set_err_recv (int /*<<< orphan*/ ,int) ; 
 int rand () ; 

__attribute__((used)) static void *sender_thread(void *arg)
{
    int i, ret = 0;
    struct sender_data *wd = arg;

    av_log(NULL, AV_LOG_INFO, "sender #%d: workload=%d\n", wd->id, wd->workload);
    for (i = 0; i < wd->workload; i++) {
        if (rand() % wd->workload < wd->workload / 10) {
            av_log(NULL, AV_LOG_INFO, "sender #%d: flushing the queue\n", wd->id);
            av_thread_message_flush(wd->queue);
        } else {
            char *val;
            AVDictionary *meta = NULL;
            struct message msg = {
                .magic = MAGIC,
                .frame = av_frame_alloc(),
            };

            if (!msg.frame) {
                ret = AVERROR(ENOMEM);
                break;
            }

            /* we add some metadata to identify the frames */
            val = av_asprintf("frame %d/%d from sender %d",
                              i + 1, wd->workload, wd->id);
            if (!val) {
                av_frame_free(&msg.frame);
                ret = AVERROR(ENOMEM);
                break;
            }
            ret = av_dict_set(&meta, "sig", val, AV_DICT_DONT_STRDUP_VAL);
            if (ret < 0) {
                av_frame_free(&msg.frame);
                break;
            }
            msg.frame->metadata = meta;

            /* allocate a real frame in order to simulate "real" work */
            msg.frame->format = AV_PIX_FMT_RGBA;
            msg.frame->width  = 320;
            msg.frame->height = 240;
            ret = av_frame_get_buffer(msg.frame, 32);
            if (ret < 0) {
                av_frame_free(&msg.frame);
                break;
            }

            /* push the frame in the common queue */
            av_log(NULL, AV_LOG_INFO, "sender #%d: sending my work (%d/%d frame:%p)\n",
                   wd->id, i + 1, wd->workload, msg.frame);
            ret = av_thread_message_queue_send(wd->queue, &msg, 0);
            if (ret < 0) {
                av_frame_free(&msg.frame);
                break;
            }
        }
    }
    av_log(NULL, AV_LOG_INFO, "sender #%d: my work is done here (%s)\n",
           wd->id, av_err2str(ret));
    av_thread_message_queue_set_err_recv(wd->queue, ret < 0 ? ret : AVERROR_EOF);
    return NULL;
}