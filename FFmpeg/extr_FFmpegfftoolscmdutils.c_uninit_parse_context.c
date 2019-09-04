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
struct TYPE_10__ {int nb_groups; struct TYPE_10__* groups; int /*<<< orphan*/  swr_opts; int /*<<< orphan*/  sws_dict; int /*<<< orphan*/  resample_opts; int /*<<< orphan*/  format_opts; int /*<<< orphan*/  codec_opts; struct TYPE_10__* opts; } ;
struct TYPE_8__ {TYPE_4__* opts; } ;
struct TYPE_7__ {TYPE_4__* opts; } ;
struct TYPE_9__ {int nb_groups; TYPE_2__ global_opts; TYPE_1__ cur_group; TYPE_4__* groups; } ;
typedef  TYPE_3__ OptionParseContext ;
typedef  TYPE_4__ OptionGroupList ;

/* Variables and functions */
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (TYPE_4__**) ; 
 int /*<<< orphan*/  uninit_opts () ; 

void uninit_parse_context(OptionParseContext *octx)
{
    int i, j;

    for (i = 0; i < octx->nb_groups; i++) {
        OptionGroupList *l = &octx->groups[i];

        for (j = 0; j < l->nb_groups; j++) {
            av_freep(&l->groups[j].opts);
            av_dict_free(&l->groups[j].codec_opts);
            av_dict_free(&l->groups[j].format_opts);
            av_dict_free(&l->groups[j].resample_opts);

            av_dict_free(&l->groups[j].sws_dict);
            av_dict_free(&l->groups[j].swr_opts);
        }
        av_freep(&l->groups);
    }
    av_freep(&octx->groups);

    av_freep(&octx->cur_group.opts);
    av_freep(&octx->global_opts.opts);

    uninit_opts();
}