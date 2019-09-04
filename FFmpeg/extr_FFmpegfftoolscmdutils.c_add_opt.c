#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char const* key; char const* val; TYPE_3__ const* opt; } ;
struct TYPE_9__ {int flags; } ;
struct TYPE_8__ {int nb_opts; TYPE_6__* opts; } ;
struct TYPE_7__ {TYPE_2__ cur_group; TYPE_2__ global_opts; } ;
typedef  TYPE_1__ OptionParseContext ;
typedef  TYPE_2__ OptionGroup ;
typedef  TYPE_3__ OptionDef ;

/* Variables and functions */
 int /*<<< orphan*/  GROW_ARRAY (TYPE_6__*,int) ; 
 int OPT_OFFSET ; 
 int OPT_PERFILE ; 
 int OPT_SPEC ; 

__attribute__((used)) static void add_opt(OptionParseContext *octx, const OptionDef *opt,
                    const char *key, const char *val)
{
    int global = !(opt->flags & (OPT_PERFILE | OPT_SPEC | OPT_OFFSET));
    OptionGroup *g = global ? &octx->global_opts : &octx->cur_group;

    GROW_ARRAY(g->opts, g->nb_opts);
    g->opts[g->nb_opts - 1].opt = opt;
    g->opts[g->nb_opts - 1].key = key;
    g->opts[g->nb_opts - 1].val = val;
}