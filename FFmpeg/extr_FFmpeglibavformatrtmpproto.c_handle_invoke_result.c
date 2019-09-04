#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_25__ {int live; double stream_id; double duration; scalar_t__ is_input; scalar_t__ playpath; scalar_t__ subscribe; } ;
typedef  int /*<<< orphan*/  RTMPPacket ;
typedef  TYPE_2__ RTMPContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int find_tracked_method (TYPE_1__*,int /*<<< orphan*/ *,int,char**) ; 
 int gen_buffer_time (TYPE_1__*,TYPE_2__*) ; 
 int gen_create_stream (TYPE_1__*,TYPE_2__*) ; 
 int gen_fcpublish_stream (TYPE_1__*,TYPE_2__*) ; 
 int gen_fcsubscribe_stream (TYPE_1__*,TYPE_2__*,scalar_t__) ; 
 int gen_get_stream_length (TYPE_1__*,TYPE_2__*) ; 
 int gen_play (TYPE_1__*,TYPE_2__*) ; 
 int gen_publish (TYPE_1__*,TYPE_2__*) ; 
 int gen_release_stream (TYPE_1__*,TYPE_2__*) ; 
 int gen_window_ack_size (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ read_number_result (int /*<<< orphan*/ *,double*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int handle_invoke_result(URLContext *s, RTMPPacket *pkt)
{
    RTMPContext *rt = s->priv_data;
    char *tracked_method = NULL;
    int ret = 0;

    if ((ret = find_tracked_method(s, pkt, 10, &tracked_method)) < 0)
        return ret;

    if (!tracked_method) {
        /* Ignore this reply when the current method is not tracked. */
        return ret;
    }

    if (!strcmp(tracked_method, "connect")) {
        if (!rt->is_input) {
            if ((ret = gen_release_stream(s, rt)) < 0)
                goto fail;

            if ((ret = gen_fcpublish_stream(s, rt)) < 0)
                goto fail;
        } else {
            if ((ret = gen_window_ack_size(s, rt)) < 0)
                goto fail;
        }

        if ((ret = gen_create_stream(s, rt)) < 0)
            goto fail;

        if (rt->is_input) {
            /* Send the FCSubscribe command when the name of live
             * stream is defined by the user or if it's a live stream. */
            if (rt->subscribe) {
                if ((ret = gen_fcsubscribe_stream(s, rt, rt->subscribe)) < 0)
                    goto fail;
            } else if (rt->live == -1) {
                if ((ret = gen_fcsubscribe_stream(s, rt, rt->playpath)) < 0)
                    goto fail;
            }
        }
    } else if (!strcmp(tracked_method, "createStream")) {
        double stream_id;
        if (read_number_result(pkt, &stream_id)) {
            av_log(s, AV_LOG_WARNING, "Unexpected reply on connect()\n");
        } else {
            rt->stream_id = stream_id;
        }

        if (!rt->is_input) {
            if ((ret = gen_publish(s, rt)) < 0)
                goto fail;
        } else {
            if (rt->live != -1) {
                if ((ret = gen_get_stream_length(s, rt)) < 0)
                    goto fail;
            }
            if ((ret = gen_play(s, rt)) < 0)
                goto fail;
            if ((ret = gen_buffer_time(s, rt)) < 0)
                goto fail;
        }
    } else if (!strcmp(tracked_method, "getStreamLength")) {
        if (read_number_result(pkt, &rt->duration)) {
            av_log(s, AV_LOG_WARNING, "Unexpected reply on getStreamLength()\n");
        }
    }

fail:
    av_free(tracked_method);
    return ret;
}