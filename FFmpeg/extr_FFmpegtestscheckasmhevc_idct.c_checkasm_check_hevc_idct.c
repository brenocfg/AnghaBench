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
typedef  int /*<<< orphan*/  HEVCDSPContext ;

/* Variables and functions */
 int /*<<< orphan*/  check_idct (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  check_idct_dc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_hevc_dsp_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  report (char*) ; 

void checkasm_check_hevc_idct(void)
{
    int bit_depth;

    for (bit_depth = 8; bit_depth <= 12; bit_depth += 2) {
        HEVCDSPContext h;

        ff_hevc_dsp_init(&h, bit_depth);
        check_idct_dc(h, bit_depth);
    }
    report("idct_dc");

    for (bit_depth = 8; bit_depth <= 12; bit_depth += 2) {
        HEVCDSPContext h;

        ff_hevc_dsp_init(&h, bit_depth);
        check_idct(h, bit_depth);
    }
    report("idct");
}