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
typedef  TYPE_1__ AVBitStreamFilter ;

/* Variables and functions */
 TYPE_1__* av_bsf_iterate (void**) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

const AVBitStreamFilter *av_bsf_get_by_name(const char *name)
{
    const AVBitStreamFilter *f = NULL;
    void *i = 0;

    if (!name)
        return NULL;

    while ((f = av_bsf_iterate(&i))) {
        if (!strcmp(f->name, name))
            return f;
    }

    return NULL;
}