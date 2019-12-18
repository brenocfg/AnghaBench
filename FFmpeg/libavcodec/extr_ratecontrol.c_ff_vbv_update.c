#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int rc_buffer_size; double const rc_min_rate; double const rc_max_rate; scalar_t__ qmax; int debug; } ;
struct TYPE_7__ {int buffer_index; } ;
struct TYPE_8__ {scalar_t__ qscale; scalar_t__ codec_id; TYPE_3__* avctx; TYPE_1__ rc_context; } ;
typedef  TYPE_1__ RateControlContext ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_MPEG4 ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FF_DEBUG_RC ; 
 scalar_t__ av_clip (int,double const,double const) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int ceil (int const) ; 
 int /*<<< orphan*/  ff_dlog (TYPE_2__*,char*,int const,int,int,double const,double const) ; 
 double get_fps (TYPE_3__*) ; 

int ff_vbv_update(MpegEncContext *s, int frame_size)
{
    RateControlContext *rcc = &s->rc_context;
    const double fps        = get_fps(s->avctx);
    const int buffer_size   = s->avctx->rc_buffer_size;
    const double min_rate   = s->avctx->rc_min_rate / fps;
    const double max_rate   = s->avctx->rc_max_rate / fps;

    ff_dlog(s, "%d %f %d %f %f\n",
            buffer_size, rcc->buffer_index, frame_size, min_rate, max_rate);

    if (buffer_size) {
        int left;

        rcc->buffer_index -= frame_size;
        if (rcc->buffer_index < 0) {
            av_log(s->avctx, AV_LOG_ERROR, "rc buffer underflow\n");
            if (frame_size > max_rate && s->qscale == s->avctx->qmax) {
                av_log(s->avctx, AV_LOG_ERROR, "max bitrate possibly too small or try trellis with large lmax or increase qmax\n");
            }
            rcc->buffer_index = 0;
        }

        left = buffer_size - rcc->buffer_index - 1;
        rcc->buffer_index += av_clip(left, min_rate, max_rate);

        if (rcc->buffer_index > buffer_size) {
            int stuffing = ceil((rcc->buffer_index - buffer_size) / 8);

            if (stuffing < 4 && s->codec_id == AV_CODEC_ID_MPEG4)
                stuffing = 4;
            rcc->buffer_index -= 8 * stuffing;

            if (s->avctx->debug & FF_DEBUG_RC)
                av_log(s->avctx, AV_LOG_DEBUG, "stuffing %d bytes\n", stuffing);

            return stuffing;
        }
    }
    return 0;
}