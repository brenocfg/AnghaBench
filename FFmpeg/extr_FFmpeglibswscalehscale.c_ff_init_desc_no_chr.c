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
struct TYPE_3__ {int /*<<< orphan*/ * process; int /*<<< orphan*/ * instance; scalar_t__ alpha; int /*<<< orphan*/ * dst; int /*<<< orphan*/ * src; } ;
typedef  int /*<<< orphan*/  SwsSlice ;
typedef  TYPE_1__ SwsFilterDescriptor ;

/* Variables and functions */
 int /*<<< orphan*/  no_chr_scale ; 

int ff_init_desc_no_chr(SwsFilterDescriptor *desc, SwsSlice * src, SwsSlice *dst)
{
    desc->src = src;
    desc->dst = dst;
    desc->alpha = 0;
    desc->instance = NULL;
    desc->process = &no_chr_scale;
    return 0;
}