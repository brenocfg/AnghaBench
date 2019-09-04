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
struct TYPE_4__ {int nb_block_sizes; int /*<<< orphan*/  fdsp; int /*<<< orphan*/ * int_table; int /*<<< orphan*/ * level_table; int /*<<< orphan*/ * run_table; int /*<<< orphan*/ * coef_vlc; int /*<<< orphan*/  hgain_vlc; scalar_t__ use_noise_coding; int /*<<< orphan*/  exp_vlc; scalar_t__ use_exp_vlc; int /*<<< orphan*/ * mdct_ctx; } ;
typedef  TYPE_1__ WMACodecContext ;
struct TYPE_5__ {TYPE_1__* priv_data; } ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_free_vlc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_mdct_end (int /*<<< orphan*/ *) ; 

int ff_wma_end(AVCodecContext *avctx)
{
    WMACodecContext *s = avctx->priv_data;
    int i;

    for (i = 0; i < s->nb_block_sizes; i++)
        ff_mdct_end(&s->mdct_ctx[i]);

    if (s->use_exp_vlc)
        ff_free_vlc(&s->exp_vlc);
    if (s->use_noise_coding)
        ff_free_vlc(&s->hgain_vlc);
    for (i = 0; i < 2; i++) {
        ff_free_vlc(&s->coef_vlc[i]);
        av_freep(&s->run_table[i]);
        av_freep(&s->level_table[i]);
        av_freep(&s->int_table[i]);
    }
    av_freep(&s->fdsp);

    return 0;
}