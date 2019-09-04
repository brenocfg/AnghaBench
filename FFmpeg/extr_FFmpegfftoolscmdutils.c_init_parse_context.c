#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__ const* group_def; } ;
struct TYPE_10__ {char* member_0; } ;
struct TYPE_8__ {char* arg; TYPE_3__ const* group_def; } ;
struct TYPE_9__ {int nb_groups; TYPE_1__ global_opts; TYPE_7__* groups; } ;
typedef  TYPE_2__ OptionParseContext ;
typedef  TYPE_3__ OptionGroupDef ;

/* Variables and functions */
 TYPE_7__* av_mallocz_array (int,int) ; 
 int /*<<< orphan*/  exit_program (int) ; 
 int /*<<< orphan*/  init_opts () ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_parse_context(OptionParseContext *octx,
                               const OptionGroupDef *groups, int nb_groups)
{
    static const OptionGroupDef global_group = { "global" };
    int i;

    memset(octx, 0, sizeof(*octx));

    octx->nb_groups = nb_groups;
    octx->groups    = av_mallocz_array(octx->nb_groups, sizeof(*octx->groups));
    if (!octx->groups)
        exit_program(1);

    for (i = 0; i < octx->nb_groups; i++)
        octx->groups[i].group_def = &groups[i];

    octx->global_opts.group_def = &global_group;
    octx->global_opts.arg       = "";

    init_opts();
}