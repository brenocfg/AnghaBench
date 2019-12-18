#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* last_dc; int dct_precision; int intra_dc_precision; TYPE_1__* avctx; } ;
struct TYPE_4__ {int bits_per_raw_sample; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */

__attribute__((used)) static void reset_studio_dc_predictors(MpegEncContext *s)
{
    /* Reset DC Predictors */
    s->last_dc[0] =
    s->last_dc[1] =
    s->last_dc[2] = 1 << (s->avctx->bits_per_raw_sample + s->dct_precision + s->intra_dc_precision - 1);
}