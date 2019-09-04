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
struct TYPE_3__ {int min_mono_subband; unsigned int* grid_3_pres; int /*<<< orphan*/  gb; scalar_t__*** grid_3_scf; } ;
typedef  TYPE_1__ DCALbrDecoder ;

/* Variables and functions */
 scalar_t__ ensure_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_dca_vlc_grid_3 ; 
 scalar_t__ parse_vlc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void parse_grid_3(DCALbrDecoder *s, int ch1, int ch2, int sb, int flag)
{
    int i, ch;

    for (ch = ch1; ch <= ch2; ch++) {
        if ((ch != ch1 && sb + 4 >= s->min_mono_subband) != flag)
            continue;

        if (s->grid_3_pres[ch] & (1U << sb))
            continue;   // Already parsed

        for (i = 0; i < 8; i++) {
            if (ensure_bits(&s->gb, 20))
                return;
            s->grid_3_scf[ch][sb][i] = parse_vlc(&s->gb, &ff_dca_vlc_grid_3, 2) - 16;
        }

        // Flag scale factors for this subband parsed
        s->grid_3_pres[ch] |= 1U << sb;
    }
}