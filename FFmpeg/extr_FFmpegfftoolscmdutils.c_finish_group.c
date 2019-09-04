#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char const* arg; int /*<<< orphan*/ * resample_opts; int /*<<< orphan*/ * format_opts; int /*<<< orphan*/ * codec_opts; int /*<<< orphan*/ * swr_opts; int /*<<< orphan*/ * sws_dict; int /*<<< orphan*/  group_def; } ;
struct TYPE_8__ {int nb_groups; int /*<<< orphan*/  group_def; TYPE_3__* groups; } ;
struct TYPE_7__ {TYPE_3__ cur_group; TYPE_2__* groups; } ;
typedef  TYPE_1__ OptionParseContext ;
typedef  TYPE_2__ OptionGroupList ;
typedef  TYPE_3__ OptionGroup ;

/* Variables and functions */
 int /*<<< orphan*/  GROW_ARRAY (TYPE_3__*,int) ; 
 int /*<<< orphan*/ * codec_opts ; 
 int /*<<< orphan*/ * format_opts ; 
 int /*<<< orphan*/  init_opts () ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * resample_opts ; 
 int /*<<< orphan*/ * swr_opts ; 
 int /*<<< orphan*/ * sws_dict ; 

__attribute__((used)) static void finish_group(OptionParseContext *octx, int group_idx,
                         const char *arg)
{
    OptionGroupList *l = &octx->groups[group_idx];
    OptionGroup *g;

    GROW_ARRAY(l->groups, l->nb_groups);
    g = &l->groups[l->nb_groups - 1];

    *g             = octx->cur_group;
    g->arg         = arg;
    g->group_def   = l->group_def;
    g->sws_dict    = sws_dict;
    g->swr_opts    = swr_opts;
    g->codec_opts  = codec_opts;
    g->format_opts = format_opts;
    g->resample_opts = resample_opts;

    codec_opts  = NULL;
    format_opts = NULL;
    resample_opts = NULL;
    sws_dict    = NULL;
    swr_opts    = NULL;
    init_opts();

    memset(&octx->cur_group, 0, sizeof(octx->cur_group));
}