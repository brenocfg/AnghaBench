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
typedef  int int32_t ;
struct TYPE_3__ {int max_exp; int ordata; int /*<<< orphan*/  shifted_both; int /*<<< orphan*/  shifted_ones; int /*<<< orphan*/  shifted_zeros; int /*<<< orphan*/  neg_zeros; int /*<<< orphan*/  false_zeros; int /*<<< orphan*/  float_flags; } ;
typedef  TYPE_1__ WavPackEncodeContext ;

/* Variables and functions */
 int /*<<< orphan*/  FLOAT_EXCEPTIONS ; 
 int get_exponent (int) ; 
 int get_mantissa (int) ; 
 scalar_t__ get_sign (int) ; 

__attribute__((used)) static void process_float(WavPackEncodeContext *s, int32_t *sample)
{
    int32_t shift_count, value, f = *sample;

    if (get_exponent(f) == 255) {
        s->float_flags |= FLOAT_EXCEPTIONS;
        value = 0x1000000;
        shift_count = 0;
    } else if (get_exponent(f)) {
        shift_count = s->max_exp - get_exponent(f);
        value = 0x800000 + get_mantissa(f);
    } else {
        shift_count = s->max_exp ? s->max_exp - 1 : 0;
        value = get_mantissa(f);
    }

    if (shift_count < 25)
        value >>= shift_count;
    else
        value = 0;

    if (!value) {
        if (get_exponent(f) || get_mantissa(f))
            s->false_zeros++;
        else if (get_sign(f))
            s->neg_zeros++;
    } else if (shift_count) {
        int32_t mask = (1 << shift_count) - 1;

        if (!(get_mantissa(f) & mask))
            s->shifted_zeros++;
        else if ((get_mantissa(f) & mask) == mask)
            s->shifted_ones++;
        else
            s->shifted_both++;
    }

    s->ordata |= value;
    *sample = get_sign(f) ? -value : value;
}