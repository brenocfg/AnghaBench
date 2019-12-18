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
typedef  int /*<<< orphan*/  AVClass ;
typedef  TYPE_1__ AVBitStreamFilter ;

/* Variables and functions */
 TYPE_1__* av_bsf_iterate (void**) ; 

const AVClass *ff_bsf_child_class_next(const AVClass *prev)
{
    const AVBitStreamFilter *f = NULL;
    void *i = 0;

    /* find the filter that corresponds to prev */
    while (prev && (f = av_bsf_iterate(&i))) {
        if (f->priv_class == prev) {
            break;
        }
    }

    /* find next filter with priv options */
    while ((f = av_bsf_iterate(&i))) {
        if (f->priv_class)
            return f->priv_class;
    }
    return NULL;
}