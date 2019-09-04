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
struct TYPE_3__ {int /*<<< orphan*/  const* priv_class; } ;
typedef  TYPE_1__ AVFilter ;
typedef  int /*<<< orphan*/  AVClass ;

/* Variables and functions */
 TYPE_1__* av_filter_iterate (void**) ; 

__attribute__((used)) static const AVClass *filter_child_class_next(const AVClass *prev)
{
    void *opaque = NULL;
    const AVFilter *f = NULL;

    /* find the filter that corresponds to prev */
    while (prev && (f = av_filter_iterate(&opaque)))
        if (f->priv_class == prev)
            break;

    /* could not find filter corresponding to prev */
    if (prev && !f)
        return NULL;

    /* find next filter with specific options */
    while ((f = av_filter_iterate(&opaque)))
        if (f->priv_class)
            return f->priv_class;

    return NULL;
}