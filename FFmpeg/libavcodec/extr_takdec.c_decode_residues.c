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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {int nb_samples; int uval; int* coding_mode; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ TAKDecContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int decode_segment (TYPE_1__*,int,int /*<<< orphan*/ *,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_unary (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int decode_residues(TAKDecContext *s, int32_t *decoded, int length)
{
    GetBitContext *gb = &s->gb;
    int i, mode, ret;

    if (length > s->nb_samples)
        return AVERROR_INVALIDDATA;

    if (get_bits1(gb)) {
        int wlength, rval;

        wlength = length / s->uval;

        rval = length - (wlength * s->uval);

        if (rval < s->uval / 2)
            rval += s->uval;
        else
            wlength++;

        if (wlength <= 1 || wlength > 128)
            return AVERROR_INVALIDDATA;

        s->coding_mode[0] = mode = get_bits(gb, 6);

        for (i = 1; i < wlength; i++) {
            int c = get_unary(gb, 1, 6);

            switch (c) {
            case 6:
                mode = get_bits(gb, 6);
                break;
            case 5:
            case 4:
            case 3: {
                /* mode += sign ? (1 - c) : (c - 1) */
                int sign = get_bits1(gb);
                mode    += (-sign ^ (c - 1)) + sign;
                break;
            }
            case 2:
                mode++;
                break;
            case 1:
                mode--;
                break;
            }
            s->coding_mode[i] = mode;
        }

        i = 0;
        while (i < wlength) {
            int len = 0;

            mode = s->coding_mode[i];
            do {
                if (i >= wlength - 1)
                    len += rval;
                else
                    len += s->uval;
                i++;

                if (i == wlength)
                    break;
            } while (s->coding_mode[i] == mode);

            if ((ret = decode_segment(s, mode, decoded, len)) < 0)
                return ret;
            decoded += len;
        }
    } else {
        mode = get_bits(gb, 6);
        if ((ret = decode_segment(s, mode, decoded, length)) < 0)
            return ret;
    }

    return 0;
}