#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int flags; } ;
struct TYPE_9__ {int output_channels; int apply_phase_inv; int /*<<< orphan*/  opusdsp; int /*<<< orphan*/  dsp; int /*<<< orphan*/  pvq; int /*<<< orphan*/ * imdct; TYPE_2__* avctx; } ;
typedef  TYPE_1__ CeltFrame ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_CODEC_FLAG_BITEXACT ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FF_ARRAY_ELEMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* av_mallocz (int) ; 
 int /*<<< orphan*/  avpriv_float_dsp_alloc (int) ; 
 int /*<<< orphan*/  ff_celt_flush (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_celt_free (TYPE_1__**) ; 
 int ff_celt_pvq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ff_mdct15_init (int /*<<< orphan*/ *,int,int,float) ; 
 int /*<<< orphan*/  ff_opus_dsp_init (int /*<<< orphan*/ *) ; 

int ff_celt_init(AVCodecContext *avctx, CeltFrame **f, int output_channels,
                 int apply_phase_inv)
{
    CeltFrame *frm;
    int i, ret;

    if (output_channels != 1 && output_channels != 2) {
        av_log(avctx, AV_LOG_ERROR, "Invalid number of output channels: %d\n",
               output_channels);
        return AVERROR(EINVAL);
    }

    frm = av_mallocz(sizeof(*frm));
    if (!frm)
        return AVERROR(ENOMEM);

    frm->avctx           = avctx;
    frm->output_channels = output_channels;
    frm->apply_phase_inv = apply_phase_inv;

    for (i = 0; i < FF_ARRAY_ELEMS(frm->imdct); i++)
        if ((ret = ff_mdct15_init(&frm->imdct[i], 1, i + 3, -1.0f/32768)) < 0)
            goto fail;

    if ((ret = ff_celt_pvq_init(&frm->pvq, 0)) < 0)
        goto fail;

    frm->dsp = avpriv_float_dsp_alloc(avctx->flags & AV_CODEC_FLAG_BITEXACT);
    if (!frm->dsp) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    ff_opus_dsp_init(&frm->opusdsp);
    ff_celt_flush(frm);

    *f = frm;

    return 0;
fail:
    ff_celt_free(&frm);
    return ret;
}