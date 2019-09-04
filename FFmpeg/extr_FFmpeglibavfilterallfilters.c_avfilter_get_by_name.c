#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ const AVFilter ;

/* Variables and functions */
 TYPE_1__ const* av_filter_iterate (void**) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

const AVFilter *avfilter_get_by_name(const char *name)
{
    const AVFilter *f = NULL;
    void *opaque = 0;

    if (!name)
        return NULL;

    while ((f = av_filter_iterate(&opaque)))
        if (!strcmp(f->name, name))
            return (AVFilter *)f;

    return NULL;
}