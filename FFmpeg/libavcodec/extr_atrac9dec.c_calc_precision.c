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
struct TYPE_6__ {int q_unit_cnt; int grad_mode; scalar_t__* gradient; int grad_boundary; } ;
struct TYPE_5__ {scalar_t__* precision_mask; scalar_t__* scalefactors; scalar_t__* precision_coarse; int* precision_fine; } ;
typedef  int /*<<< orphan*/  ATRAC9Context ;
typedef  TYPE_1__ ATRAC9ChannelData ;
typedef  TYPE_2__ ATRAC9BlockData ;

/* Variables and functions */
 int FFABS (scalar_t__) ; 
 scalar_t__ FFMAX (scalar_t__,int) ; 
 scalar_t__ FFMIN (int const,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void calc_precision(ATRAC9Context *s, ATRAC9BlockData *b,
                                  ATRAC9ChannelData *c)
{
    memset(c->precision_mask, 0, sizeof(c->precision_mask));
    for (int i = 1; i < b->q_unit_cnt; i++) {
        const int delta = FFABS(c->scalefactors[i] - c->scalefactors[i - 1]) - 1;
        if (delta > 0) {
            const int neg = c->scalefactors[i - 1] > c->scalefactors[i];
            c->precision_mask[i - neg] += FFMIN(delta, 5);
        }
    }

    if (b->grad_mode) {
        for (int i = 0; i < b->q_unit_cnt; i++) {
            c->precision_coarse[i] = c->scalefactors[i];
            c->precision_coarse[i] += c->precision_mask[i] - b->gradient[i];
            if (c->precision_coarse[i] < 0)
                continue;
            switch (b->grad_mode) {
            case 1:
                c->precision_coarse[i] >>= 1;
                break;
            case 2:
                c->precision_coarse[i] = (3 * c->precision_coarse[i]) >> 3;
                break;
            case 3:
                c->precision_coarse[i] >>= 2;
                break;
            }
        }
    } else {
        for (int i = 0; i < b->q_unit_cnt; i++)
            c->precision_coarse[i] = c->scalefactors[i] - b->gradient[i];
    }


    for (int i = 0; i < b->q_unit_cnt; i++)
        c->precision_coarse[i] = FFMAX(c->precision_coarse[i], 1);

    for (int i = 0; i < b->grad_boundary; i++)
        c->precision_coarse[i]++;

    for (int i = 0; i < b->q_unit_cnt; i++) {
        c->precision_fine[i] = 0;
        if (c->precision_coarse[i] > 15) {
            c->precision_fine[i] = c->precision_coarse[i] - 15;
            c->precision_coarse[i] = 15;
        }
    }
}