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
struct TYPE_7__ {TYPE_1__ const* (* child_class_next ) (TYPE_1__ const*) ;} ;
typedef  TYPE_1__ AVClass ;

/* Variables and functions */
 TYPE_1__ const* stub1 (TYPE_1__ const*) ; 

const AVClass *av_opt_child_class_next(const AVClass *parent, const AVClass *prev)
{
    if (parent->child_class_next)
        return parent->child_class_next(prev);
    return NULL;
}