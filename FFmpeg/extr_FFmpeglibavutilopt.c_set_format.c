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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum AVOptionType { ____Placeholder_AVOptionType } AVOptionType ;
struct TYPE_3__ {int type; int offset; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
typedef  TYPE_1__ AVOption ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_OPTION_NOT_FOUND ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERANGE ; 
 int FFMAX (int /*<<< orphan*/ ,int) ; 
 int FFMIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* av_opt_find2 (void*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,void**) ; 

__attribute__((used)) static int set_format(void *obj, const char *name, int fmt, int search_flags,
                      enum AVOptionType type, const char *desc, int nb_fmts)
{
    void *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0,
                                     search_flags, &target_obj);
    int min, max;

    if (!o || !target_obj)
        return AVERROR_OPTION_NOT_FOUND;
    if (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value set by option '%s' is not a %s format", name, desc);
        return AVERROR(EINVAL);
    }

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    if (fmt < min || fmt > max) {
        av_log(obj, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        return AVERROR(ERANGE);
    }
    *(int *)(((uint8_t *)target_obj) + o->offset) = fmt;
    return 0;
}