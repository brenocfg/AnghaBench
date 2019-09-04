#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int output_channels; int /*<<< orphan*/ * avctx; } ;
typedef  TYPE_1__ SilkContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* av_mallocz (int) ; 
 int /*<<< orphan*/  ff_silk_flush (TYPE_1__*) ; 

int ff_silk_init(AVCodecContext *avctx, SilkContext **ps, int output_channels)
{
    SilkContext *s;

    if (output_channels != 1 && output_channels != 2) {
        av_log(avctx, AV_LOG_ERROR, "Invalid number of output channels: %d\n",
               output_channels);
        return AVERROR(EINVAL);
    }

    s = av_mallocz(sizeof(*s));
    if (!s)
        return AVERROR(ENOMEM);

    s->avctx           = avctx;
    s->output_channels = output_channels;

    ff_silk_flush(s);

    *ps = s;

    return 0;
}