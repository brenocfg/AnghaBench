#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const uint8_t ;
struct TYPE_4__ {size_t bandwidth; } ;
struct TYPE_5__ {int /*<<< orphan*/  avctx; TYPE_1__ packet; int /*<<< orphan*/  swr; int /*<<< orphan*/  silk_samplerate; } ;
typedef  TYPE_2__ OpusStreamContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_opt_set_int (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * silk_resample_delay ; 
 int swr_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/ ) ; 
 int swr_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int opus_init_resample(OpusStreamContext *s)
{
    static const float delay[16] = { 0.0 };
    const uint8_t *delayptr[2] = { (uint8_t*)delay, (uint8_t*)delay };
    int ret;

    av_opt_set_int(s->swr, "in_sample_rate", s->silk_samplerate, 0);
    ret = swr_init(s->swr);
    if (ret < 0) {
        av_log(s->avctx, AV_LOG_ERROR, "Error opening the resampler.\n");
        return ret;
    }

    ret = swr_convert(s->swr,
                      NULL, 0,
                      delayptr, silk_resample_delay[s->packet.bandwidth]);
    if (ret < 0) {
        av_log(s->avctx, AV_LOG_ERROR,
               "Error feeding initial silence to the resampler.\n");
        return ret;
    }

    return 0;
}