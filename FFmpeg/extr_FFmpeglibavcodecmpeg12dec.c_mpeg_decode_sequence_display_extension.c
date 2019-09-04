#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int debug; void* colorspace; void* color_trc; void* color_primaries; } ;
struct TYPE_6__ {int width; int height; } ;
struct TYPE_7__ {TYPE_5__* avctx; int /*<<< orphan*/  gb; } ;
struct TYPE_8__ {TYPE_1__ pan_scan; TYPE_2__ mpeg_enc_ctx; } ;
typedef  TYPE_2__ MpegEncContext ;
typedef  TYPE_3__ Mpeg1Context ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int FF_DEBUG_PICT_INFO ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int,int) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void mpeg_decode_sequence_display_extension(Mpeg1Context *s1)
{
    MpegEncContext *s = &s1->mpeg_enc_ctx;
    int color_description, w, h;

    skip_bits(&s->gb, 3); /* video format */
    color_description = get_bits1(&s->gb);
    if (color_description) {
        s->avctx->color_primaries = get_bits(&s->gb, 8);
        s->avctx->color_trc       = get_bits(&s->gb, 8);
        s->avctx->colorspace      = get_bits(&s->gb, 8);
    }
    w = get_bits(&s->gb, 14);
    skip_bits(&s->gb, 1); // marker
    h = get_bits(&s->gb, 14);
    // remaining 3 bits are zero padding

    s1->pan_scan.width  = 16 * w;
    s1->pan_scan.height = 16 * h;

    if (s->avctx->debug & FF_DEBUG_PICT_INFO)
        av_log(s->avctx, AV_LOG_DEBUG, "sde w:%d, h:%d\n", w, h);
}