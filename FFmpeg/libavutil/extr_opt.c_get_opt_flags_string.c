#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
typedef  int /*<<< orphan*/  flags ;
struct TYPE_5__ {int i64; } ;
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/  name; TYPE_1__ default_val; int /*<<< orphan*/  unit; } ;
typedef  TYPE_2__ AVOption ;

/* Variables and functions */
 scalar_t__ AV_OPT_TYPE_CONST ; 
 TYPE_2__* av_opt_next (void*,TYPE_2__ const*) ; 
 char* av_strdup (char*) ; 
 int /*<<< orphan*/  av_strlcatf (char*,int,char*,...) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static char *get_opt_flags_string(void *obj, const char *unit, int64_t value)
{
    const AVOption *opt = NULL;
    char flags[512];

    flags[0] = 0;
    if (!unit)
        return NULL;
    while ((opt = av_opt_next(obj, opt))) {
        if (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 & value) {
            if (flags[0])
                av_strlcatf(flags, sizeof(flags), "+");
            av_strlcatf(flags, sizeof(flags), "%s", opt->name);
        }
    }
    if (flags[0])
        return av_strdup(flags);
    return NULL;
}