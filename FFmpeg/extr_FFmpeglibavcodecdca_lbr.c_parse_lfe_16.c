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
struct TYPE_3__ {float* lfe_data; float lfe_scale; int /*<<< orphan*/  gb; int /*<<< orphan*/  avctx; } ;
typedef  TYPE_1__ DCALbrDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FF_ARRAY_ELEMS (float*) ; 
 int av_clip (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__* ff_dca_lfe_delta_index_16 ; 
 float* ff_dca_lfe_step_size_16 ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int parse_lfe_16(DCALbrDecoder *s)
{
    int step_max = FF_ARRAY_ELEMS(ff_dca_lfe_step_size_16) - 1;
    int i, ps, si, code, step_i;
    float step, value, delta;

    ps = get_bits(&s->gb, 16);
    si = ps >> 15;

    value = (((ps & 0x7fff) ^ -si) + si) * (1.0f / 0x7fff);

    step_i = get_bits(&s->gb, 8);
    if (step_i > step_max) {
        av_log(s->avctx, AV_LOG_ERROR, "Invalid LFE step size index\n");
        return -1;
    }

    step = ff_dca_lfe_step_size_16[step_i];

    for (i = 0; i < 64; i++) {
        code = get_bits(&s->gb, 4);

        delta = step * 0.125f;
        if (code & 4)
            delta += step;
        if (code & 2)
            delta += step * 0.5f;
        if (code & 1)
            delta += step * 0.25f;

        if (code & 8) {
            value -= delta;
            if (value < -3.0f)
                value = -3.0f;
        } else {
            value += delta;
            if (value > 3.0f)
                value = 3.0f;
        }

        step_i += ff_dca_lfe_delta_index_16[code & 7];
        step_i = av_clip(step_i, 0, step_max);

        step = ff_dca_lfe_step_size_16[step_i];
        s->lfe_data[i] = value * s->lfe_scale;
    }

    return 0;
}