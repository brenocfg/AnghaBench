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
struct TYPE_4__ {int /*<<< orphan*/  lfe_quant; int /*<<< orphan*/  lfe_peak_cb; int /*<<< orphan*/  lfe_scale_factor; scalar_t__ lfe_channel; } ;
typedef  TYPE_1__ DCAEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  calc_one_scale (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void calc_lfe_scales(DCAEncContext *c)
{
    if (c->lfe_channel)
        c->lfe_scale_factor = calc_one_scale(c, c->lfe_peak_cb, 11, &c->lfe_quant);
}