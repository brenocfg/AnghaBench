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
 int /*<<< orphan*/  check_sao_band (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  check_sao_edge (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_hevc_dsp_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  report (char*) ; 

void checkasm_check_hevc_sao(void)
{
    int bit_depth;

    for (bit_depth = 8; bit_depth <= 12; bit_depth += 2) {
        HEVCDSPContext h;

        ff_hevc_dsp_init(&h, bit_depth);
        check_sao_band(h, bit_depth);
    }
    report("sao_band");

    for (bit_depth = 8; bit_depth <= 12; bit_depth += 2) {
        HEVCDSPContext h;

        ff_hevc_dsp_init(&h, bit_depth);
        check_sao_edge(h, bit_depth);
    }
    report("sao_edge");
}