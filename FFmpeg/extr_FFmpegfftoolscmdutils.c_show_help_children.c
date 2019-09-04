#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ option; } ;
typedef  TYPE_1__ AVClass ;

/* Variables and functions */
 TYPE_1__* av_opt_child_class_next (TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  av_opt_show2 (TYPE_1__ const**,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

void show_help_children(const AVClass *class, int flags)
{
    const AVClass *child = NULL;
    if (class->option) {
        av_opt_show2(&class, NULL, flags, 0);
        printf("\n");
    }

    while (child = av_opt_child_class_next(class, child))
        show_help_children(child, flags);
}