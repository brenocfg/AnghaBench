#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_12__ {scalar_t__ codec_id; } ;
struct TYPE_11__ {int ConfigBitstreamRaw; int /*<<< orphan*/  guidConfigBitstreamEncryption; } ;
struct TYPE_10__ {int ConfigBitstreamRaw; int /*<<< orphan*/  guidConfigBitstreamEncryption; } ;
struct TYPE_9__ {scalar_t__ pix_fmt; } ;
typedef  int /*<<< orphan*/  GUID ;
typedef  TYPE_1__ FFDXVASharedContext ;
typedef  TYPE_2__ DXVA2_ConfigPictureDecode ;
typedef  TYPE_3__ D3D11_VIDEO_DECODER_CONFIG ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_CODEC_ID_H264 ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 scalar_t__ AV_PIX_FMT_D3D11 ; 
 scalar_t__ AV_PIX_FMT_DXVA2_VLD ; 
 TYPE_1__* DXVA_SHARED_CONTEXT (TYPE_4__*) ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_DXVA2_NoEncrypt ; 

__attribute__((used)) static int dxva_get_decoder_configuration(AVCodecContext *avctx,
                                          const void *cfg_list,
                                          unsigned cfg_count)
{
    FFDXVASharedContext *sctx = DXVA_SHARED_CONTEXT(avctx);
    unsigned i, best_score = 0;
    int best_cfg = -1;

    for (i = 0; i < cfg_count; i++) {
        unsigned score;
        UINT ConfigBitstreamRaw;
        GUID guidConfigBitstreamEncryption;

#if CONFIG_D3D11VA
        if (sctx->pix_fmt == AV_PIX_FMT_D3D11) {
            D3D11_VIDEO_DECODER_CONFIG *cfg = &((D3D11_VIDEO_DECODER_CONFIG *)cfg_list)[i];
            ConfigBitstreamRaw = cfg->ConfigBitstreamRaw;
            guidConfigBitstreamEncryption = cfg->guidConfigBitstreamEncryption;
        }
#endif
#if CONFIG_DXVA2
        if (sctx->pix_fmt == AV_PIX_FMT_DXVA2_VLD) {
            DXVA2_ConfigPictureDecode *cfg = &((DXVA2_ConfigPictureDecode *)cfg_list)[i];
            ConfigBitstreamRaw = cfg->ConfigBitstreamRaw;
            guidConfigBitstreamEncryption = cfg->guidConfigBitstreamEncryption;
        }
#endif

        if (ConfigBitstreamRaw == 1)
            score = 1;
        else if (avctx->codec_id == AV_CODEC_ID_H264 && ConfigBitstreamRaw == 2)
            score = 2;
        else
            continue;
        if (IsEqualGUID(&guidConfigBitstreamEncryption, &ff_DXVA2_NoEncrypt))
            score += 16;
        if (score > best_score) {
            best_score = score;
            best_cfg = i;
        }
    }

    if (!best_score) {
        av_log(avctx, AV_LOG_VERBOSE, "No valid decoder configuration available\n");
        return AVERROR(EINVAL);
    }

    return best_cfg;
}