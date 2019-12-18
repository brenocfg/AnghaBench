#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* dst; } ;
struct TYPE_6__ {TYPE_1__* plane; } ;
struct TYPE_5__ {scalar_t__ available_lines; scalar_t__ sliceH; scalar_t__ sliceY; } ;
typedef  TYPE_3__ SwsFilterDescriptor ;
typedef  int /*<<< orphan*/  SwsContext ;

/* Variables and functions */

__attribute__((used)) static int no_chr_scale(SwsContext *c, SwsFilterDescriptor *desc, int sliceY, int sliceH)
{
    desc->dst->plane[1].sliceY = sliceY + sliceH - desc->dst->plane[1].available_lines;
    desc->dst->plane[1].sliceH = desc->dst->plane[1].available_lines;
    desc->dst->plane[2].sliceY = sliceY + sliceH - desc->dst->plane[2].available_lines;
    desc->dst->plane[2].sliceH = desc->dst->plane[2].available_lines;
    return 0;
}