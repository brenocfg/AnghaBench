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
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int version; int (* query_ranges ) (TYPE_1__**,void*,char const*,int) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  nb_components; } ;
typedef  TYPE_1__ AVOptionRanges ;
typedef  TYPE_3__ AVClass ;

/* Variables and functions */
 int AV_OPT_MULTI_COMPONENT_RANGE ; 
 int av_opt_query_ranges_default (TYPE_1__**,void*,char const*,int) ; 

int av_opt_query_ranges(AVOptionRanges **ranges_arg, void *obj, const char *key, int flags)
{
    int ret;
    const AVClass *c = *(AVClass**)obj;
    int (*callback)(AVOptionRanges **, void *obj, const char *key, int flags) = NULL;

    if (c->version > (52 << 16 | 11 << 8))
        callback = c->query_ranges;

    if (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, key, flags);
    if (ret >= 0) {
        if (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    return ret;
}