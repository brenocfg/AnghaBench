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
struct vpx_codec_enc_cfg {int dummy; } ;
struct TYPE_5__ {scalar_t__ codec_id; int /*<<< orphan*/  bit_rate; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_VP9 ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  set_vp8_defaults (TYPE_1__*,struct vpx_codec_enc_cfg*) ; 
 int /*<<< orphan*/  set_vp9_defaults (TYPE_1__*,struct vpx_codec_enc_cfg*) ; 

__attribute__((used)) static void set_vpx_defaults(AVCodecContext *avctx,
                             struct vpx_codec_enc_cfg *enccfg)
{
    av_assert0(!avctx->bit_rate);
#if CONFIG_LIBVPX_VP9_ENCODER
    if (avctx->codec_id == AV_CODEC_ID_VP9) {
        set_vp9_defaults(avctx, enccfg);
        return;
    }
#endif
    set_vp8_defaults(avctx, enccfg);
}