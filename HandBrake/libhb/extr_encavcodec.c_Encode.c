#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_16__ ;

/* Type definitions */
struct TYPE_26__ {TYPE_16__* context; int /*<<< orphan*/  file; TYPE_5__* job; int /*<<< orphan*/  frameno_in; int /*<<< orphan*/  chapter_queue; } ;
typedef  TYPE_6__ hb_work_private_t ;
struct TYPE_27__ {TYPE_6__* private_data; } ;
typedef  TYPE_7__ hb_work_object_t ;
struct TYPE_24__ {scalar_t__ new_chap; } ;
struct TYPE_22__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_28__ {TYPE_4__ s; TYPE_3__* plane; TYPE_2__ f; } ;
typedef  TYPE_8__ hb_buffer_t ;
typedef  int /*<<< orphan*/  hb_buffer_list_t ;
struct TYPE_21__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_29__ {int key_frame; scalar_t__ pts; int /*<<< orphan*/  quality; int /*<<< orphan*/  pict_type; int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__ member_0; } ;
struct TYPE_25__ {scalar_t__ pass_id; scalar_t__ chapter_markers; } ;
struct TYPE_23__ {int /*<<< orphan*/  stride; int /*<<< orphan*/  data; } ;
struct TYPE_20__ {char* stats_out; int /*<<< orphan*/  global_quality; } ;
typedef  TYPE_9__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 scalar_t__ HB_PASS_ENCODE_1ST ; 
 int avcodec_send_frame (TYPE_16__*,TYPE_9__*) ; 
 int /*<<< orphan*/  compute_dts_offset (TYPE_6__*,TYPE_8__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  get_packets (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_chapter_enqueue (int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  hb_log (char*) ; 
 int /*<<< orphan*/  save_frame_info (TYPE_6__*,TYPE_8__*) ; 

__attribute__((used)) static void Encode( hb_work_object_t *w, hb_buffer_t *in,
                    hb_buffer_list_t *list )
{
    hb_work_private_t * pv = w->private_data;
    AVFrame             frame = {{0}};
    int                 ret;

    frame.width       = in->f.width;
    frame.height      = in->f.height;
    frame.data[0]     = in->plane[0].data;
    frame.data[1]     = in->plane[1].data;
    frame.data[2]     = in->plane[2].data;
    frame.linesize[0] = in->plane[0].stride;
    frame.linesize[1] = in->plane[1].stride;
    frame.linesize[2] = in->plane[2].stride;

    if (in->s.new_chap > 0 && pv->job->chapter_markers)
    {
        /* chapters have to start with an IDR frame so request that this
           frame be coded as IDR. Since there may be multiple frames
           currently buffered in the encoder remember the timestamp so
           when this frame finally pops out of the encoder we'll mark
           its buffer as the start of a chapter. */
        frame.pict_type = AV_PICTURE_TYPE_I;
        frame.key_frame = 1;
        hb_chapter_enqueue(pv->chapter_queue, in);
    }

    // For constant quality, setting the quality in AVCodecContext
    // doesn't do the trick.  It must be set in the AVFrame.
    frame.quality = pv->context->global_quality;

    // Bizarro ffmpeg requires timestamp time_base to be == framerate
    // for the encoders we care about.  It writes AVCodecContext.time_base
    // to the framerate field of encoded bitstream headers, so if we
    // want correct bitstreams, we must set time_base = framerate.
    // We can't pass timestamps that are not based on the time_base
    // because encoders require accurately based timestamps in order to
    // do proper rate control.
    //
    // I.e. ffmpeg doesn't support VFR timestamps.
    //
    // Because of this, we have to do some fugly things, like storing
    // PTS values and computing DTS ourselves.
    //
    // Remember timestamp info about this frame
    save_frame_info(pv, in);
    compute_dts_offset(pv, in);

    frame.pts = pv->frameno_in++;

    // Encode
    ret = avcodec_send_frame(pv->context, &frame);
    if (ret < 0)
    {
        hb_log("encavcodec: avcodec_send_frame failed");
        return;
    }

    // Write stats
    if (pv->job->pass_id == HB_PASS_ENCODE_1ST &&
        pv->context->stats_out != NULL)
    {
        fprintf( pv->file, "%s", pv->context->stats_out );
    }

    get_packets(w, list);
}