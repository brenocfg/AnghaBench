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
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int w; int h; int /*<<< orphan*/  format; TYPE_3__* dst; } ;
struct TYPE_5__ {int codeword_length; int codebook_length; int /*<<< orphan*/  rgba_map; void* codebook; void* codeword_closest_codebook_idxs; void* codeword; int /*<<< orphan*/  pix_desc; } ;
typedef  TYPE_1__ ELBGContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int NB_COMPONENTS ; 
 int /*<<< orphan*/  av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 void* av_realloc_f (void*,int,int) ; 
 int /*<<< orphan*/  ff_fill_rgba_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    ELBGContext *elbg = ctx->priv;

    elbg->pix_desc = av_pix_fmt_desc_get(inlink->format);
    elbg->codeword_length = inlink->w * inlink->h;
    elbg->codeword = av_realloc_f(elbg->codeword, elbg->codeword_length,
                                  NB_COMPONENTS * sizeof(*elbg->codeword));
    if (!elbg->codeword)
        return AVERROR(ENOMEM);

    elbg->codeword_closest_codebook_idxs =
        av_realloc_f(elbg->codeword_closest_codebook_idxs, elbg->codeword_length,
                     sizeof(*elbg->codeword_closest_codebook_idxs));
    if (!elbg->codeword_closest_codebook_idxs)
        return AVERROR(ENOMEM);

    elbg->codebook = av_realloc_f(elbg->codebook, elbg->codebook_length,
                                  NB_COMPONENTS * sizeof(*elbg->codebook));
    if (!elbg->codebook)
        return AVERROR(ENOMEM);

    ff_fill_rgba_map(elbg->rgba_map, inlink->format);

    return 0;
}