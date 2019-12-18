#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
struct TYPE_4__ {int channels; scalar_t__ channel_layout; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EINVAL ; 
 int FF_ARRAY_ELEMS (scalar_t__*) ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 int /*<<< orphan*/  av_get_channel_layout_string (char*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__* ff_vorbis_channel_layouts ; 

__attribute__((used)) static int libopus_check_vorbis_layout(AVCodecContext *avctx, int mapping_family) {
    av_assert2(avctx->channels < FF_ARRAY_ELEMS(ff_vorbis_channel_layouts));

    if (!avctx->channel_layout) {
        av_log(avctx, AV_LOG_WARNING,
               "No channel layout specified. Opus encoder will use Vorbis "
               "channel layout for %d channels.\n", avctx->channels);
    } else if (avctx->channel_layout != ff_vorbis_channel_layouts[avctx->channels - 1]) {
        char name[32];
        av_get_channel_layout_string(name, sizeof(name), avctx->channels,
                                     avctx->channel_layout);
        av_log(avctx, AV_LOG_ERROR,
               "Invalid channel layout %s for specified mapping family %d.\n",
               name, mapping_family);

        return AVERROR(EINVAL);
    }

    return 0;
}