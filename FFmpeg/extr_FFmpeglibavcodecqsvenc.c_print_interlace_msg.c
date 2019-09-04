#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ CodecId; scalar_t__ CodecProfile; scalar_t__ CodecLevel; } ;
struct TYPE_6__ {TYPE_1__ mfx; } ;
struct TYPE_7__ {TYPE_2__ param; } ;
typedef  TYPE_3__ QSVEncContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ MFX_CODEC_AVC ; 
 scalar_t__ MFX_LEVEL_AVC_21 ; 
 scalar_t__ MFX_LEVEL_AVC_41 ; 
 scalar_t__ MFX_PROFILE_AVC_BASELINE ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void print_interlace_msg(AVCodecContext *avctx, QSVEncContext *q)
{
    if (q->param.mfx.CodecId == MFX_CODEC_AVC) {
        if (q->param.mfx.CodecProfile == MFX_PROFILE_AVC_BASELINE ||
            q->param.mfx.CodecLevel < MFX_LEVEL_AVC_21 ||
            q->param.mfx.CodecLevel > MFX_LEVEL_AVC_41)
            av_log(avctx, AV_LOG_WARNING,
                   "Interlaced coding is supported"
                   " at Main/High Profile Level 2.2-4.0\n");
    }
}