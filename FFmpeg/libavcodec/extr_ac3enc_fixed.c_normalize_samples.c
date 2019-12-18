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
struct TYPE_4__ {int (* ac3_max_msb_abs_int16 ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ac3_lshift_int16 ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  windowed_samples; TYPE_1__ ac3dsp; } ;
typedef  TYPE_2__ AC3EncodeContext ;

/* Variables and functions */
 int /*<<< orphan*/  AC3_WINDOW_SIZE ; 
 int av_log2 (int) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int normalize_samples(AC3EncodeContext *s)
{
    int v = s->ac3dsp.ac3_max_msb_abs_int16(s->windowed_samples, AC3_WINDOW_SIZE);
    v = 14 - av_log2(v);
    if (v > 0)
        s->ac3dsp.ac3_lshift_int16(s->windowed_samples, AC3_WINDOW_SIZE, v);
    /* +6 to right-shift from 31-bit to 25-bit */
    return v + 6;
}