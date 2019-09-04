#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int debug; scalar_t__ idct_algo; TYPE_3__* priv_data; } ;
struct TYPE_7__ {int /*<<< orphan*/ ** avg_qpel_pixels_tab; int /*<<< orphan*/ ** put_no_rnd_qpel_pixels_tab; int /*<<< orphan*/ ** put_qpel_pixels_tab; } ;
struct TYPE_8__ {scalar_t__ codec_tag; scalar_t__ vo_type; int workaround_bugs; int padding_bug_score; scalar_t__ codec_id; scalar_t__ divx_packed; int /*<<< orphan*/  avctx; TYPE_1__ qdsp; } ;
struct TYPE_9__ {int xvid_build; int divx_version; int lavc_build; scalar_t__ vol_control_parameters; int divx_build; TYPE_2__ m; } ;
typedef  TYPE_2__ MpegEncContext ;
typedef  TYPE_3__ Mpeg4DecContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_MPEG4 ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 scalar_t__ AV_RL32 (char*) ; 
 scalar_t__ CONFIG_MPEG4_DECODER ; 
 int FF_BUG_AUTODETECT ; 
 int FF_BUG_DC_CLIP ; 
 int FF_BUG_DIRECT_BLOCKSIZE ; 
 int FF_BUG_EDGE ; 
 int FF_BUG_HPEL_CHROMA ; 
 int FF_BUG_IEDGE ; 
 int FF_BUG_QPEL_CHROMA ; 
 int FF_BUG_QPEL_CHROMA2 ; 
 int FF_BUG_STD_QPEL ; 
 int FF_BUG_UMP4 ; 
 int FF_BUG_XVID_ILACE ; 
 int FF_DEBUG_BUGS ; 
 scalar_t__ FF_IDCT_AUTO ; 
 scalar_t__ FF_IDCT_XVID ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,unsigned int,unsigned int,int,char*) ; 
 int /*<<< orphan*/  ff_avg_qpel16_mc11_old_c ; 
 int /*<<< orphan*/  ff_avg_qpel16_mc12_old_c ; 
 int /*<<< orphan*/  ff_avg_qpel16_mc13_old_c ; 
 int /*<<< orphan*/  ff_avg_qpel16_mc31_old_c ; 
 int /*<<< orphan*/  ff_avg_qpel16_mc32_old_c ; 
 int /*<<< orphan*/  ff_avg_qpel16_mc33_old_c ; 
 int /*<<< orphan*/  ff_avg_qpel8_mc11_old_c ; 
 int /*<<< orphan*/  ff_avg_qpel8_mc12_old_c ; 
 int /*<<< orphan*/  ff_avg_qpel8_mc13_old_c ; 
 int /*<<< orphan*/  ff_avg_qpel8_mc31_old_c ; 
 int /*<<< orphan*/  ff_avg_qpel8_mc32_old_c ; 
 int /*<<< orphan*/  ff_avg_qpel8_mc33_old_c ; 
 int /*<<< orphan*/  ff_mpv_idct_init (TYPE_2__*) ; 
 int /*<<< orphan*/  ff_put_no_rnd_qpel16_mc11_old_c ; 
 int /*<<< orphan*/  ff_put_no_rnd_qpel16_mc12_old_c ; 
 int /*<<< orphan*/  ff_put_no_rnd_qpel16_mc13_old_c ; 
 int /*<<< orphan*/  ff_put_no_rnd_qpel16_mc31_old_c ; 
 int /*<<< orphan*/  ff_put_no_rnd_qpel16_mc32_old_c ; 
 int /*<<< orphan*/  ff_put_no_rnd_qpel16_mc33_old_c ; 
 int /*<<< orphan*/  ff_put_no_rnd_qpel8_mc11_old_c ; 
 int /*<<< orphan*/  ff_put_no_rnd_qpel8_mc12_old_c ; 
 int /*<<< orphan*/  ff_put_no_rnd_qpel8_mc13_old_c ; 
 int /*<<< orphan*/  ff_put_no_rnd_qpel8_mc31_old_c ; 
 int /*<<< orphan*/  ff_put_no_rnd_qpel8_mc32_old_c ; 
 int /*<<< orphan*/  ff_put_no_rnd_qpel8_mc33_old_c ; 
 int /*<<< orphan*/  ff_put_qpel16_mc11_old_c ; 
 int /*<<< orphan*/  ff_put_qpel16_mc12_old_c ; 
 int /*<<< orphan*/  ff_put_qpel16_mc13_old_c ; 
 int /*<<< orphan*/  ff_put_qpel16_mc31_old_c ; 
 int /*<<< orphan*/  ff_put_qpel16_mc32_old_c ; 
 int /*<<< orphan*/  ff_put_qpel16_mc33_old_c ; 
 int /*<<< orphan*/  ff_put_qpel8_mc11_old_c ; 
 int /*<<< orphan*/  ff_put_qpel8_mc12_old_c ; 
 int /*<<< orphan*/  ff_put_qpel8_mc13_old_c ; 
 int /*<<< orphan*/  ff_put_qpel8_mc31_old_c ; 
 int /*<<< orphan*/  ff_put_qpel8_mc32_old_c ; 
 int /*<<< orphan*/  ff_put_qpel8_mc33_old_c ; 

int ff_mpeg4_workaround_bugs(AVCodecContext *avctx)
{
    Mpeg4DecContext *ctx = avctx->priv_data;
    MpegEncContext *s = &ctx->m;

    if (ctx->xvid_build == -1 && ctx->divx_version == -1 && ctx->lavc_build == -1) {
        if (s->codec_tag        == AV_RL32("XVID") ||
            s->codec_tag        == AV_RL32("XVIX") ||
            s->codec_tag        == AV_RL32("RMP4") ||
            s->codec_tag        == AV_RL32("ZMP4") ||
            s->codec_tag        == AV_RL32("SIPP"))
            ctx->xvid_build = 0;
    }

    if (ctx->xvid_build == -1 && ctx->divx_version == -1 && ctx->lavc_build == -1)
        if (s->codec_tag == AV_RL32("DIVX") && s->vo_type == 0 &&
            ctx->vol_control_parameters == 0)
            ctx->divx_version = 400;  // divx 4

    if (ctx->xvid_build >= 0 && ctx->divx_version >= 0) {
        ctx->divx_version =
        ctx->divx_build   = -1;
    }

    if (s->workaround_bugs & FF_BUG_AUTODETECT) {
        if (s->codec_tag == AV_RL32("XVIX"))
            s->workaround_bugs |= FF_BUG_XVID_ILACE;

        if (s->codec_tag == AV_RL32("UMP4"))
            s->workaround_bugs |= FF_BUG_UMP4;

        if (ctx->divx_version >= 500 && ctx->divx_build < 1814)
            s->workaround_bugs |= FF_BUG_QPEL_CHROMA;

        if (ctx->divx_version > 502 && ctx->divx_build < 1814)
            s->workaround_bugs |= FF_BUG_QPEL_CHROMA2;

        if (ctx->xvid_build <= 3U)
            s->padding_bug_score = 256 * 256 * 256 * 64;

        if (ctx->xvid_build <= 1U)
            s->workaround_bugs |= FF_BUG_QPEL_CHROMA;

        if (ctx->xvid_build <= 12U)
            s->workaround_bugs |= FF_BUG_EDGE;

        if (ctx->xvid_build <= 32U)
            s->workaround_bugs |= FF_BUG_DC_CLIP;

#define SET_QPEL_FUNC(postfix1, postfix2)                           \
    s->qdsp.put_        ## postfix1 = ff_put_        ## postfix2;   \
    s->qdsp.put_no_rnd_ ## postfix1 = ff_put_no_rnd_ ## postfix2;   \
    s->qdsp.avg_        ## postfix1 = ff_avg_        ## postfix2;

        if (ctx->lavc_build < 4653U)
            s->workaround_bugs |= FF_BUG_STD_QPEL;

        if (ctx->lavc_build < 4655U)
            s->workaround_bugs |= FF_BUG_DIRECT_BLOCKSIZE;

        if (ctx->lavc_build < 4670U)
            s->workaround_bugs |= FF_BUG_EDGE;

        if (ctx->lavc_build <= 4712U)
            s->workaround_bugs |= FF_BUG_DC_CLIP;

        if ((ctx->lavc_build&0xFF) >= 100) {
            if (ctx->lavc_build > 3621476 && ctx->lavc_build < 3752552 &&
               (ctx->lavc_build < 3752037 || ctx->lavc_build > 3752191) // 3.2.1+
            )
                s->workaround_bugs |= FF_BUG_IEDGE;
        }

        if (ctx->divx_version >= 0)
            s->workaround_bugs |= FF_BUG_DIRECT_BLOCKSIZE;
        if (ctx->divx_version == 501 && ctx->divx_build == 20020416)
            s->padding_bug_score = 256 * 256 * 256 * 64;

        if (ctx->divx_version < 500U)
            s->workaround_bugs |= FF_BUG_EDGE;

        if (ctx->divx_version >= 0)
            s->workaround_bugs |= FF_BUG_HPEL_CHROMA;
    }

    if (s->workaround_bugs & FF_BUG_STD_QPEL) {
        SET_QPEL_FUNC(qpel_pixels_tab[0][5], qpel16_mc11_old_c)
        SET_QPEL_FUNC(qpel_pixels_tab[0][7], qpel16_mc31_old_c)
        SET_QPEL_FUNC(qpel_pixels_tab[0][9], qpel16_mc12_old_c)
        SET_QPEL_FUNC(qpel_pixels_tab[0][11], qpel16_mc32_old_c)
        SET_QPEL_FUNC(qpel_pixels_tab[0][13], qpel16_mc13_old_c)
        SET_QPEL_FUNC(qpel_pixels_tab[0][15], qpel16_mc33_old_c)

        SET_QPEL_FUNC(qpel_pixels_tab[1][5], qpel8_mc11_old_c)
        SET_QPEL_FUNC(qpel_pixels_tab[1][7], qpel8_mc31_old_c)
        SET_QPEL_FUNC(qpel_pixels_tab[1][9], qpel8_mc12_old_c)
        SET_QPEL_FUNC(qpel_pixels_tab[1][11], qpel8_mc32_old_c)
        SET_QPEL_FUNC(qpel_pixels_tab[1][13], qpel8_mc13_old_c)
        SET_QPEL_FUNC(qpel_pixels_tab[1][15], qpel8_mc33_old_c)
    }

    if (avctx->debug & FF_DEBUG_BUGS)
        av_log(s->avctx, AV_LOG_DEBUG,
               "bugs: %X lavc_build:%d xvid_build:%d divx_version:%d divx_build:%d %s\n",
               s->workaround_bugs, ctx->lavc_build, ctx->xvid_build,
               ctx->divx_version, ctx->divx_build, s->divx_packed ? "p" : "");

    if (CONFIG_MPEG4_DECODER && ctx->xvid_build >= 0 &&
        s->codec_id == AV_CODEC_ID_MPEG4 &&
        avctx->idct_algo == FF_IDCT_AUTO) {
        avctx->idct_algo = FF_IDCT_XVID;
        ff_mpv_idct_init(s);
        return 1;
    }

    return 0;
}