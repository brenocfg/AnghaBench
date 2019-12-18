#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int i_type; scalar_t__ b_keyframe; int /*<<< orphan*/  i_dts; int /*<<< orphan*/  i_pts; } ;
typedef  TYPE_3__ x264_picture_t ;
struct TYPE_19__ {int i_payload; int i_type; scalar_t__ i_ref_idc; int /*<<< orphan*/  p_payload; } ;
typedef  TYPE_4__ x264_nal_t ;
struct TYPE_20__ {int /*<<< orphan*/  chapter_queue; TYPE_7__* job; } ;
typedef  TYPE_5__ hb_work_private_t ;
struct TYPE_21__ {TYPE_1__* config; TYPE_5__* private_data; } ;
typedef  TYPE_6__ hb_work_object_t ;
struct TYPE_22__ {int /*<<< orphan*/  inline_parameter_sets; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_7__ hb_job_t ;
struct TYPE_17__ {scalar_t__ frametype; int /*<<< orphan*/  flags; int /*<<< orphan*/  renderOffset; void* stop; int /*<<< orphan*/  start; void* duration; } ;
struct TYPE_23__ {int size; TYPE_2__ s; scalar_t__ data; } ;
typedef  TYPE_8__ hb_buffer_t ;
struct TYPE_16__ {int /*<<< orphan*/  init_delay; } ;

/* Variables and functions */
 void* AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  HB_FLAG_FRAMETYPE_KEY ; 
 int /*<<< orphan*/  HB_FLAG_FRAMETYPE_REF ; 
 scalar_t__ HB_FRAME_B ; 
 void* HB_FRAME_BREF ; 
 scalar_t__ HB_FRAME_I ; 
 scalar_t__ HB_FRAME_IDR ; 
 scalar_t__ HB_FRAME_P ; 
#define  NAL_PPS 137 
 scalar_t__ NAL_PRIORITY_DISPOSABLE ; 
#define  NAL_SEI 136 
#define  NAL_SLICE 135 
#define  NAL_SLICE_IDR 134 
#define  NAL_SPS 133 
#define  X264_TYPE_B 132 
#define  X264_TYPE_BREF 131 
#define  X264_TYPE_I 130 
#define  X264_TYPE_IDR 129 
#define  X264_TYPE_P 128 
 int /*<<< orphan*/  hb_buffer_close (TYPE_8__**) ; 
 int /*<<< orphan*/  hb_chapter_dequeue (int /*<<< orphan*/ ,TYPE_8__*) ; 
 TYPE_8__* hb_video_buffer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static hb_buffer_t *nal_encode( hb_work_object_t *w, x264_picture_t *pic_out,
                                int i_nal, x264_nal_t *nal )
{
    hb_buffer_t *buf = NULL;
    hb_work_private_t *pv = w->private_data;
    hb_job_t *job = pv->job;

    /* Should be way too large */
    buf = hb_video_buffer_init( job->width, job->height );
    buf->size = 0;
    buf->s.frametype = 0;

    // use the pts to get the original frame's duration.
    buf->s.duration     = AV_NOPTS_VALUE;
    buf->s.start        = pic_out->i_pts;
    buf->s.stop         = AV_NOPTS_VALUE;
    buf->s.renderOffset = pic_out->i_dts;
    if ( !w->config->init_delay && pic_out->i_dts < 0 )
    {
        w->config->init_delay = -pic_out->i_dts;
    }

    /* Determine what type of frame we have. */
    switch (pic_out->i_type)
    {
        case X264_TYPE_IDR:
            buf->s.frametype = HB_FRAME_IDR;
            break;

        case X264_TYPE_P:
            buf->s.frametype = HB_FRAME_P;
            break;

        case X264_TYPE_B:
            buf->s.frametype = HB_FRAME_B;
            break;

        case X264_TYPE_BREF:
            buf->s.frametype = HB_FRAME_BREF;
            break;

        case X264_TYPE_I:
        default:
            buf->s.frametype = HB_FRAME_I;
            break;
    }
    buf->s.flags = 0;

    if (pic_out->b_keyframe)
    {
        buf->s.flags |= HB_FLAG_FRAMETYPE_KEY;
        /* if we have a chapter marker pending and this
           frame's presentation time stamp is at or after
           the marker's time stamp, use this as the
           chapter start. */
        hb_chapter_dequeue(pv->chapter_queue, buf);
    }

    /* Encode all the NALs we were given into buf.
       NOTE: This code assumes one video frame per NAL (but there can
             be other stuff like SPS and/or PPS). If there are multiple
             frames we only get the duration of the first which will
             eventually screw up the muxer & decoder. */
    int i;
    buf->s.flags &= ~HB_FLAG_FRAMETYPE_REF;
    for( i = 0; i < i_nal; i++ )
    {
        int size = nal[i].i_payload;
        memcpy(buf->data + buf->size, nal[i].p_payload, size);
        if( size < 1 )
        {
            continue;
        }

        /* H.264 in .mp4 or .mkv */
        switch( nal[i].i_type )
        {
            /* Sequence Parameter Set & Program Parameter Set go in the
             * mp4 header so skip them here
             */
            case NAL_SPS:
            case NAL_PPS:
                if (!job->inline_parameter_sets)
                {
                    continue;
                }
                break;

            case NAL_SLICE_IDR:
            case NAL_SLICE:
            case NAL_SEI:
            default:
                break;
        }

        /*
         * Expose disposable bit to muxer.
         *
         * Also, since libx264 doesn't tell us when B-frames are
         * themselves reference frames, figure it out on our own.
         */
        if (nal[i].i_ref_idc != NAL_PRIORITY_DISPOSABLE)
        {
            if (buf->s.frametype == HB_FRAME_B)
            {
                buf->s.frametype  = HB_FRAME_BREF;
            }
            buf->s.flags |= HB_FLAG_FRAMETYPE_REF;
        }

        buf->size += size;
    }
    // make sure we found at least one video frame
    if ( buf->size <= 0 )
    {
        // no video - discard the buf
        hb_buffer_close( &buf );
    }
    return buf;
}