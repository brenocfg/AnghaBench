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
struct iec61883_data {scalar_t__ type; int /*<<< orphan*/  raw1394; int /*<<< orphan*/  bandwidth; int /*<<< orphan*/  channel; int /*<<< orphan*/  input_port; int /*<<< orphan*/  output_port; int /*<<< orphan*/  node; TYPE_1__* queue_first; TYPE_1__* dv_demux; int /*<<< orphan*/  iec61883_dv; int /*<<< orphan*/  mpeg_demux; int /*<<< orphan*/  iec61883_mpeg2; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; int /*<<< orphan*/  receive_task_thread; scalar_t__ thread_loop; } ;
struct TYPE_6__ {struct iec61883_data* priv_data; } ;
struct TYPE_5__ {struct TYPE_5__* buf; struct TYPE_5__* next; } ;
typedef  TYPE_1__ DVPacket ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ CONFIG_MPEGTS_DEMUXER ; 
 scalar_t__ IEC61883_HDV ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 int /*<<< orphan*/  avpriv_mpegts_parse_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iec61883_cmp_disconnect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iec61883_dv_fb_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iec61883_dv_fb_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iec61883_mpeg2_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iec61883_mpeg2_recv_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw1394_destroy_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw1394_get_local_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iec61883_close(AVFormatContext *context)
{
    struct iec61883_data *dv = context->priv_data;

#if THREADS
    dv->thread_loop = 0;
    pthread_join(dv->receive_task_thread, NULL);
    pthread_cond_destroy(&dv->cond);
    pthread_mutex_destroy(&dv->mutex);
#endif

    if (CONFIG_MPEGTS_DEMUXER && dv->type == IEC61883_HDV) {
        iec61883_mpeg2_recv_stop(dv->iec61883_mpeg2);
        iec61883_mpeg2_close(dv->iec61883_mpeg2);
        avpriv_mpegts_parse_close(dv->mpeg_demux);
    } else {
        iec61883_dv_fb_stop(dv->iec61883_dv);
        iec61883_dv_fb_close(dv->iec61883_dv);
        av_freep(&dv->dv_demux);
    }
    while (dv->queue_first) {
        DVPacket *packet = dv->queue_first;
        dv->queue_first = packet->next;
        av_freep(&packet->buf);
        av_freep(&packet);
    }

    iec61883_cmp_disconnect(dv->raw1394, dv->node, dv->output_port,
                            raw1394_get_local_id(dv->raw1394),
                            dv->input_port, dv->channel, dv->bandwidth);

    raw1394_destroy_handle(dv->raw1394);

    return 0;
}