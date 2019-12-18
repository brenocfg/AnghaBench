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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/ * table; } ;
struct TYPE_5__ {int /*<<< orphan*/ * process; int /*<<< orphan*/ * dst; int /*<<< orphan*/ * src; TYPE_2__* instance; } ;
typedef  int /*<<< orphan*/  SwsSlice ;
typedef  TYPE_1__ SwsFilterDescriptor ;
typedef  TYPE_2__ GammaContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_2__* av_malloc (int) ; 
 int /*<<< orphan*/  gamma_convert ; 

int ff_init_gamma_convert(SwsFilterDescriptor *desc, SwsSlice * src, uint16_t *table)
{
    GammaContext *li = av_malloc(sizeof(GammaContext));
    if (!li)
        return AVERROR(ENOMEM);
    li->table = table;

    desc->instance = li;
    desc->src = src;
    desc->dst = NULL;
    desc->process = &gamma_convert;

    return 0;
}