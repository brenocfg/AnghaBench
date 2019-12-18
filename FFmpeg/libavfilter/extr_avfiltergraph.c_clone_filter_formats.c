#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nb_formats; struct TYPE_6__* formats; int /*<<< orphan*/ * refs; scalar_t__ refcount; } ;
typedef  TYPE_1__ AVFilterFormats ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 void* av_memdup (TYPE_1__*,int) ; 

__attribute__((used)) static AVFilterFormats *clone_filter_formats(AVFilterFormats *arg)
{
    AVFilterFormats *a = av_memdup(arg, sizeof(*arg));
    if (a) {
        a->refcount = 0;
        a->refs     = NULL;
        a->formats  = av_memdup(a->formats, sizeof(*a->formats) * a->nb_formats);
        if (!a->formats && arg->formats)
            av_freep(&a);
    }
    return a;
}