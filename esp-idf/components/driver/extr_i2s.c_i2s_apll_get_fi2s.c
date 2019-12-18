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
typedef  int uint32_t ;

/* Variables and functions */
 float APLL_MAX_FREQ ; 
 float APLL_MIN_FREQ ; 
 int /*<<< orphan*/  EFUSE_BLK0_RDATA3_REG ; 
 scalar_t__ GET_PERI_REG_BITS2 (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ rtc_clk_xtal_freq_get () ; 

__attribute__((used)) static float i2s_apll_get_fi2s(int bits_per_sample, int sdm0, int sdm1, int sdm2, int odir)
{
    int f_xtal = (int)rtc_clk_xtal_freq_get() * 1000000;
#ifdef CONFIG_IDF_TARGET_ESP32
    uint32_t is_rev0 = (GET_PERI_REG_BITS2(EFUSE_BLK0_RDATA3_REG, 1, 15) == 0);
    if (is_rev0) {
        sdm0 = 0;
        sdm1 = 0;
    }
#elif defined CONFIG_IDF_TARGET_ESP32S2BETA
    sdm0 = 0;
    sdm1 = 0;
#endif
    float fout = f_xtal * (sdm2 + sdm1 / 256.0f + sdm0 / 65536.0f + 4);
    if (fout < APLL_MIN_FREQ || fout > APLL_MAX_FREQ) {
        return APLL_MAX_FREQ;
    }
    float fpll = fout / (2 * (odir+2)); //== fi2s (N=1, b=0, a=1)
    return fpll/2;
}