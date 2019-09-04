#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int argc_min; unsigned int argc_max; int (* func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,unsigned int,char**,int /*<<< orphan*/ ) ;int /*<<< orphan*/  tag; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  AVFilterContext ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 unsigned int FF_ARRAY_ELEMS (TYPE_1__*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,...) ; 
 TYPE_1__* functions ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,unsigned int,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eval_function(AVFilterContext *ctx, AVBPrint *bp, char *fct,
                         unsigned argc, char **argv)
{
    unsigned i;

    for (i = 0; i < FF_ARRAY_ELEMS(functions); i++) {
        if (strcmp(fct, functions[i].name))
            continue;
        if (argc < functions[i].argc_min) {
            av_log(ctx, AV_LOG_ERROR, "%%{%s} requires at least %d arguments\n",
                   fct, functions[i].argc_min);
            return AVERROR(EINVAL);
        }
        if (argc > functions[i].argc_max) {
            av_log(ctx, AV_LOG_ERROR, "%%{%s} requires at most %d arguments\n",
                   fct, functions[i].argc_max);
            return AVERROR(EINVAL);
        }
        break;
    }
    if (i >= FF_ARRAY_ELEMS(functions)) {
        av_log(ctx, AV_LOG_ERROR, "%%{%s} is not known\n", fct);
        return AVERROR(EINVAL);
    }
    return functions[i].func(ctx, bp, fct, argc, argv, functions[i].tag);
}