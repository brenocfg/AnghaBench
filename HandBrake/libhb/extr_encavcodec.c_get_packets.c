#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_19__ {int /*<<< orphan*/  chapter_queue; int /*<<< orphan*/  context; } ;
typedef  TYPE_2__ hb_work_private_t ;
struct TYPE_20__ {TYPE_2__* private_data; } ;
typedef  TYPE_3__ hb_work_object_t ;
struct TYPE_18__ {int /*<<< orphan*/  flags; scalar_t__ frametype; scalar_t__ duration; scalar_t__ stop; int /*<<< orphan*/  start; } ;
struct TYPE_21__ {TYPE_1__ s; int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  TYPE_4__ hb_buffer_t ;
typedef  int /*<<< orphan*/  hb_buffer_list_t ;
struct TYPE_22__ {int flags; int /*<<< orphan*/  size; int /*<<< orphan*/  pts; int /*<<< orphan*/  data; } ;
typedef  TYPE_5__ AVPacket ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  HB_FLAG_FRAMETYPE_KEY ; 
 int /*<<< orphan*/  HB_FLAG_FRAMETYPE_REF ; 
 int /*<<< orphan*/  av_init_packet (TYPE_5__*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_5__*) ; 
 int avcodec_receive_packet (int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ get_frame_duration (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_frame_start (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* hb_buffer_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_buffer_list_append (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  hb_chapter_dequeue (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  hb_log (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* process_delay_list (TYPE_2__*,TYPE_4__*) ; 

__attribute__((used)) static void get_packets( hb_work_object_t * w, hb_buffer_list_t * list )
{
    hb_work_private_t * pv = w->private_data;

    while (1)
    {
        int           ret;
        AVPacket      pkt;
        hb_buffer_t * out;

        av_init_packet(&pkt);
        ret = avcodec_receive_packet(pv->context, &pkt);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
        {
            break;
        }
        if (ret < 0)
        {
            hb_log("encavcodec: avcodec_receive_packet failed");
        }

        out = hb_buffer_init(pkt.size);
        memcpy(out->data, pkt.data, out->size);

        int64_t frameno = pkt.pts;
        out->size       = pkt.size;
        out->s.start    = get_frame_start(pv, frameno);
        out->s.duration = get_frame_duration(pv, frameno);
        out->s.stop     = out->s.stop + out->s.duration;
        // libav 12 deprecated context->coded_frame, so we can't determine
        // the exact frame type any more. So until I can completely
        // wire up ffmpeg with AV_PKT_DISPOSABLE_FRAME, all frames
        // must be considered to potentially be reference frames
        out->s.flags     = HB_FLAG_FRAMETYPE_REF;
        out->s.frametype = 0;
        if (pkt.flags & AV_PKT_FLAG_KEY)
        {
            out->s.flags |= HB_FLAG_FRAMETYPE_KEY;
            hb_chapter_dequeue(pv->chapter_queue, out);
        }
        out = process_delay_list(pv, out);

        hb_buffer_list_append(list, out);
        av_packet_unref(&pkt);
    }
}