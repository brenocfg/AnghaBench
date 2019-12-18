#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_17__ {int /*<<< orphan*/  new_chap; int /*<<< orphan*/  scr_sequence; int /*<<< orphan*/  pts; scalar_t__ sequence; } ;
typedef  TYPE_1__ reordered_data_t ;
struct TYPE_18__ {int frametype; int discard; int /*<<< orphan*/  new_chap; int /*<<< orphan*/  scr_sequence; int /*<<< orphan*/  pts; scalar_t__ size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ packet_info_t ;
struct TYPE_19__ {int /*<<< orphan*/  decode_errors; int /*<<< orphan*/  frame; int /*<<< orphan*/  context; TYPE_8__* palette; int /*<<< orphan*/  sequence; } ;
typedef  TYPE_3__ hb_work_private_t ;
struct TYPE_21__ {int /*<<< orphan*/  data; int /*<<< orphan*/  size; } ;
struct TYPE_20__ {int flags; scalar_t__ size; int /*<<< orphan*/ * data; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; } ;
typedef  TYPE_4__ AVPacket ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AVPALETTE_SIZE ; 
 int AV_LOG_QUIET ; 
 int /*<<< orphan*/  AV_PKT_DATA_PALETTE ; 
 int AV_PKT_FLAG_DISCARD ; 
 int AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  EAGAIN ; 
 int HB_FRAME_MASK_KEY ; 
 int MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_init_packet (TYPE_4__*) ; 
 int av_log_get_level () ; 
 int /*<<< orphan*/  av_log_set_level (int) ; 
 int /*<<< orphan*/ * av_packet_new_side_data (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_4__*) ; 
 int avcodec_receive_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int avcodec_send_packet (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  compute_frame_duration (TYPE_3__*) ; 
 int /*<<< orphan*/  filter_video (TYPE_3__*) ; 
 int global_verbosity_level ; 
 int /*<<< orphan*/  hb_buffer_close (TYPE_8__**) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reordered_hash_add (TYPE_3__*,TYPE_1__*) ; 

__attribute__((used)) static int decodeFrame( hb_work_private_t * pv, packet_info_t * packet_info )
{
    int got_picture = 0, oldlevel = 0, ret;
    AVPacket avp;
    reordered_data_t * reordered;

    if ( global_verbosity_level <= 1 )
    {
        oldlevel = av_log_get_level();
        av_log_set_level( AV_LOG_QUIET );
    }

    av_init_packet(&avp);
    if (packet_info != NULL)
    {
        avp.data = packet_info->data;
        avp.size = packet_info->size;
        avp.pts  = pv->sequence;
        avp.dts  = pv->sequence;
        reordered = malloc(sizeof(*reordered));
        if (reordered != NULL)
        {
            reordered->sequence     = pv->sequence++;
            reordered->pts          = packet_info->pts;
            reordered->scr_sequence = packet_info->scr_sequence;
            reordered->new_chap     = packet_info->new_chap;
            reordered_hash_add(pv, reordered);
        }

        // libav avcodec video decoder needs AVPacket flagged with
        // AV_PKT_FLAG_KEY for some codecs. For example, sequence of
        // PNG in a mov container.
        if (packet_info->frametype & HB_FRAME_MASK_KEY)
        {
            avp.flags |= AV_PKT_FLAG_KEY;
        }
        avp.flags  |= packet_info->discard * AV_PKT_FLAG_DISCARD;
    }
    else
    {
        avp.data = NULL;
        avp.size = 0;
    }

    if (pv->palette != NULL)
    {
        uint8_t * palette;
        int size;
        palette = av_packet_new_side_data(&avp, AV_PKT_DATA_PALETTE,
                                          AVPALETTE_SIZE);
        size = MIN(pv->palette->size, AVPALETTE_SIZE);
        memcpy(palette, pv->palette->data, size);
        hb_buffer_close(&pv->palette);
    }

    ret = avcodec_send_packet(pv->context, &avp);
    av_packet_unref(&avp);
    if (ret < 0 && ret != AVERROR_EOF)
    {
        ++pv->decode_errors;
        return 0;
    }

    do
    {
        ret = avcodec_receive_frame(pv->context, pv->frame);
        if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF)
        {
            ++pv->decode_errors;
        }
        if (ret < 0)
        {
            break;
        }
        got_picture = 1;

        // recompute the frame/field duration, because sometimes it changes
        compute_frame_duration( pv );
        filter_video(pv);
    } while (ret >= 0);

    if ( global_verbosity_level <= 1 )
    {
        av_log_set_level( oldlevel );
    }

    return got_picture;
}