#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ sample_fmt; int /*<<< orphan*/ * priv_data; } ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_1__ AVCodecContext ;
typedef  int /*<<< orphan*/  ATDecodeContext ;

/* Variables and functions */
 scalar_t__ AV_SAMPLE_FMT_S32 ; 
 int /*<<< orphan*/  COPY_SAMPLES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int16_t ; 
 int /*<<< orphan*/  int32_t ; 

__attribute__((used)) static void ffat_copy_samples(AVCodecContext *avctx, AVFrame *frame)
{
    ATDecodeContext *at = avctx->priv_data;
    if (avctx->sample_fmt == AV_SAMPLE_FMT_S32) {
        COPY_SAMPLES(int32_t);
    } else {
        COPY_SAMPLES(int16_t);
    }
}