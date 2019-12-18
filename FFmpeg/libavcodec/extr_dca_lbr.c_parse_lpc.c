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
struct TYPE_3__ {int framenum; int /*<<< orphan*/ **** lpc_coeff; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ DCALbrDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  convert_lpc (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ ensure_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int parse_lpc(DCALbrDecoder *s, int ch1, int ch2, int start_sb, int end_sb)
{
    int f = s->framenum & 1;
    int i, sb, ch, codes[16];

    // First two subbands have two sets of coefficients, third subband has one
    for (sb = start_sb; sb < end_sb; sb++) {
        int ncodes = 8 * (1 + (sb < 2));
        for (ch = ch1; ch <= ch2; ch++) {
            if (ensure_bits(&s->gb, 4 * ncodes))
                return 0;
            for (i = 0; i < ncodes; i++)
                codes[i] = get_bits(&s->gb, 4);
            for (i = 0; i < ncodes / 8; i++)
                convert_lpc(s->lpc_coeff[f][ch][sb][i], &codes[i * 8]);
        }
    }

    return 0;
}