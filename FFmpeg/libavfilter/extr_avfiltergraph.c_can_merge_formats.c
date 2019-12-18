#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVMediaType { ____Placeholder_AVMediaType } AVMediaType ;
struct TYPE_13__ {struct TYPE_13__* formats; struct TYPE_13__* refs; } ;
typedef  TYPE_1__ AVFilterFormats ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 TYPE_1__* clone_filter_formats (TYPE_1__*) ; 
 TYPE_1__* ff_merge_formats (TYPE_1__*,TYPE_1__*,int) ; 
 TYPE_1__* ff_merge_samplerates (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static int can_merge_formats(AVFilterFormats *a_arg,
                             AVFilterFormats *b_arg,
                             enum AVMediaType type,
                             int is_sample_rate)
{
    AVFilterFormats *a, *b, *ret;
    if (a_arg == b_arg)
        return 1;
    a = clone_filter_formats(a_arg);
    b = clone_filter_formats(b_arg);

    if (!a || !b) {
        if (a)
            av_freep(&a->formats);
        if (b)
            av_freep(&b->formats);

        av_freep(&a);
        av_freep(&b);

        return 0;
    }

    if (is_sample_rate) {
        ret = ff_merge_samplerates(a, b);
    } else {
        ret = ff_merge_formats(a, b, type);
    }
    if (ret) {
        av_freep(&ret->formats);
        av_freep(&ret->refs);
        av_freep(&ret);
        return 1;
    } else {
        if (a)
            av_freep(&a->formats);
        if (b)
            av_freep(&b->formats);
        av_freep(&a);
        av_freep(&b);
        return 0;
    }
}