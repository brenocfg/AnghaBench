#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int int8_t ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int qdm2_get_se_vlc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int qdm2_get_vlc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_tab_diff ; 
 int /*<<< orphan*/  vlc_tab_level ; 
 int /*<<< orphan*/  vlc_tab_run ; 

__attribute__((used)) static int init_quantized_coeffs_elem0(int8_t *quantized_coeffs,
                                        GetBitContext *gb)
{
    int i, k, run, level, diff;

    if (get_bits_left(gb) < 16)
        return -1;
    level = qdm2_get_vlc(gb, &vlc_tab_level, 0, 2);

    quantized_coeffs[0] = level;

    for (i = 0; i < 7; ) {
        if (get_bits_left(gb) < 16)
            return -1;
        run = qdm2_get_vlc(gb, &vlc_tab_run, 0, 1) + 1;

        if (i + run >= 8)
            return -1;

        if (get_bits_left(gb) < 16)
            return -1;
        diff = qdm2_get_se_vlc(&vlc_tab_diff, gb, 2);

        for (k = 1; k <= run; k++)
            quantized_coeffs[i + k] = (level + ((k * diff) / run));

        level += diff;
        i += run;
    }
    return 0;
}