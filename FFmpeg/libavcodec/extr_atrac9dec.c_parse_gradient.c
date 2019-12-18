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
typedef  float uint8_t ;
struct TYPE_6__ {int grad_mode; int grad_boundary; int q_unit_cnt; int* gradient; } ;
struct TYPE_5__ {float** alloc_curve; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ ATRAC9Context ;
typedef  TYPE_2__ ATRAC9BlockData ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int FFABS (int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int parse_gradient(ATRAC9Context *s, ATRAC9BlockData *b,
                                 GetBitContext *gb)
{
    int grad_range[2];
    int grad_value[2];
    int values, sign, base;
    uint8_t *curve;
    float scale;

    b->grad_mode = get_bits(gb, 2);
    if (b->grad_mode) {
        grad_range[0] = get_bits(gb, 5);
        grad_range[1] = 31;
        grad_value[0] = get_bits(gb, 5);
        grad_value[1] = 31;
    } else {
        grad_range[0] = get_bits(gb, 6);
        grad_range[1] = get_bits(gb, 6) + 1;
        grad_value[0] = get_bits(gb, 5);
        grad_value[1] = get_bits(gb, 5);
    }
    b->grad_boundary = get_bits(gb, 4);

    if (grad_range[0] >= grad_range[1] || grad_range[1] > 31)
        return AVERROR_INVALIDDATA;

    if (b->grad_boundary > b->q_unit_cnt)
        return AVERROR_INVALIDDATA;

    values    = grad_value[1] - grad_value[0];
    sign      = 1 - 2*(values < 0);
    base      = grad_value[0] + sign;
    scale     = (FFABS(values) - 1) / 31.0f;
    curve     = s->alloc_curve[grad_range[1] - grad_range[0] - 1];

    for (int i = 0; i <= b->q_unit_cnt; i++)
        b->gradient[i] = grad_value[i >= grad_range[0]];

    for (int i = grad_range[0]; i < grad_range[1]; i++)
        b->gradient[i] = base + sign*((int)(scale*curve[i - grad_range[0]]));

    return 0;
}