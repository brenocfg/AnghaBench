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
struct TYPE_6__ {int /*<<< orphan*/ ** coeff; TYPE_1__* filter_params; } ;
struct TYPE_5__ {int order; int /*<<< orphan*/  coeff_bits; int /*<<< orphan*/  coeff_shift; int /*<<< orphan*/  shift; } ;
typedef  TYPE_1__ FilterParams ;
typedef  TYPE_2__ ChannelParams ;

/* Variables and functions */

__attribute__((used)) static void copy_filter_params(ChannelParams *dst_cp, ChannelParams *src_cp, int filter)
{
    FilterParams *dst = &dst_cp->filter_params[filter];
    FilterParams *src = &src_cp->filter_params[filter];
    unsigned int order;

    dst->order = src->order;

    if (dst->order) {
        dst->shift = src->shift;

        dst->coeff_shift = src->coeff_shift;
        dst->coeff_bits = src->coeff_bits;
    }

    for (order = 0; order < dst->order; order++)
        dst_cp->coeff[filter][order] = src_cp->coeff[filter][order];
}