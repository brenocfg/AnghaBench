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
struct TYPE_6__ {TYPE_1__ const* option; } ;
struct TYPE_5__ {scalar_t__ name; } ;
typedef  TYPE_1__ AVOption ;
typedef  TYPE_2__ AVClass ;

/* Variables and functions */

const AVOption *av_opt_next(const void *obj, const AVOption *last)
{
    const AVClass *class;
    if (!obj)
        return NULL;
    class = *(const AVClass**)obj;
    if (!last && class && class->option && class->option[0].name)
        return class->option;
    if (last && last[1].name)
        return ++last;
    return NULL;
}