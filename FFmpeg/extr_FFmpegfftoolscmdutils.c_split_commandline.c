#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int flags; int /*<<< orphan*/  help; int /*<<< orphan*/  name; } ;
struct TYPE_18__ {int /*<<< orphan*/  name; } ;
struct TYPE_16__ {scalar_t__ nb_opts; } ;
struct TYPE_17__ {TYPE_1__ cur_group; } ;
typedef  TYPE_2__ OptionParseContext ;
typedef  TYPE_3__ OptionGroupDef ;
typedef  TYPE_4__ OptionDef ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_OPTION_NOT_FOUND ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EINVAL ; 
 int HAS_ARG ; 
 int OPT_BOOL ; 
 int OPT_EXIT ; 
 int /*<<< orphan*/  add_opt (TYPE_2__*,TYPE_4__ const*,char const*,char const*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ codec_opts ; 
 TYPE_4__* find_option (TYPE_4__ const*,char const*) ; 
 int /*<<< orphan*/  finish_group (TYPE_2__*,int,char const*) ; 
 scalar_t__ format_opts ; 
 int /*<<< orphan*/  init_parse_context (TYPE_2__*,TYPE_3__ const*,int) ; 
 int match_group_separator (TYPE_3__ const*,int,char const*) ; 
 int opt_default (int /*<<< orphan*/ *,char const*,char*) ; 
 int /*<<< orphan*/  prepare_app_arguments (int*,char***) ; 
 scalar_t__ resample_opts ; 

int split_commandline(OptionParseContext *octx, int argc, char *argv[],
                      const OptionDef *options,
                      const OptionGroupDef *groups, int nb_groups)
{
    int optindex = 1;
    int dashdash = -2;

    /* perform system-dependent conversions for arguments list */
    prepare_app_arguments(&argc, &argv);

    init_parse_context(octx, groups, nb_groups);
    av_log(NULL, AV_LOG_DEBUG, "Splitting the commandline.\n");

    while (optindex < argc) {
        const char *opt = argv[optindex++], *arg;
        const OptionDef *po;
        int ret;

        av_log(NULL, AV_LOG_DEBUG, "Reading option '%s' ...", opt);

        if (opt[0] == '-' && opt[1] == '-' && !opt[2]) {
            dashdash = optindex;
            continue;
        }
        /* unnamed group separators, e.g. output filename */
        if (opt[0] != '-' || !opt[1] || dashdash+1 == optindex) {
            finish_group(octx, 0, opt);
            av_log(NULL, AV_LOG_DEBUG, " matched as %s.\n", groups[0].name);
            continue;
        }
        opt++;

#define GET_ARG(arg)                                                           \
do {                                                                           \
    arg = argv[optindex++];                                                    \
    if (!arg) {                                                                \
        av_log(NULL, AV_LOG_ERROR, "Missing argument for option '%s'.\n", opt);\
        return AVERROR(EINVAL);                                                \
    }                                                                          \
} while (0)

        /* named group separators, e.g. -i */
        if ((ret = match_group_separator(groups, nb_groups, opt)) >= 0) {
            GET_ARG(arg);
            finish_group(octx, ret, arg);
            av_log(NULL, AV_LOG_DEBUG, " matched as %s with argument '%s'.\n",
                   groups[ret].name, arg);
            continue;
        }

        /* normal options */
        po = find_option(options, opt);
        if (po->name) {
            if (po->flags & OPT_EXIT) {
                /* optional argument, e.g. -h */
                arg = argv[optindex++];
            } else if (po->flags & HAS_ARG) {
                GET_ARG(arg);
            } else {
                arg = "1";
            }

            add_opt(octx, po, opt, arg);
            av_log(NULL, AV_LOG_DEBUG, " matched as option '%s' (%s) with "
                   "argument '%s'.\n", po->name, po->help, arg);
            continue;
        }

        /* AVOptions */
        if (argv[optindex]) {
            ret = opt_default(NULL, opt, argv[optindex]);
            if (ret >= 0) {
                av_log(NULL, AV_LOG_DEBUG, " matched as AVOption '%s' with "
                       "argument '%s'.\n", opt, argv[optindex]);
                optindex++;
                continue;
            } else if (ret != AVERROR_OPTION_NOT_FOUND) {
                av_log(NULL, AV_LOG_ERROR, "Error parsing option '%s' "
                       "with argument '%s'.\n", opt, argv[optindex]);
                return ret;
            }
        }

        /* boolean -nofoo options */
        if (opt[0] == 'n' && opt[1] == 'o' &&
            (po = find_option(options, opt + 2)) &&
            po->name && po->flags & OPT_BOOL) {
            add_opt(octx, po, opt, "0");
            av_log(NULL, AV_LOG_DEBUG, " matched as option '%s' (%s) with "
                   "argument 0.\n", po->name, po->help);
            continue;
        }

        av_log(NULL, AV_LOG_ERROR, "Unrecognized option '%s'.\n", opt);
        return AVERROR_OPTION_NOT_FOUND;
    }

    if (octx->cur_group.nb_opts || codec_opts || format_opts || resample_opts)
        av_log(NULL, AV_LOG_WARNING, "Trailing options were found on the "
               "commandline.\n");

    av_log(NULL, AV_LOG_DEBUG, "Finished splitting the commandline.\n");

    return 0;
}