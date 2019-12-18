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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int LEDC_DIV_NUM_HSTIMER0_V ; 
 int /*<<< orphan*/  _ledcSetupTimer (int,int,int,int) ; 
 int getApbFrequency () ; 

__attribute__((used)) static double _ledcSetupTimerFreq(uint8_t chan, double freq, uint8_t bit_num)
{
    uint64_t clk_freq = getApbFrequency();
    clk_freq <<= 8;//div_num is 8 bit decimal
    uint32_t div_num = (clk_freq >> bit_num) / freq;
    bool apb_clk = true;
    if(div_num > LEDC_DIV_NUM_HSTIMER0_V) {
        clk_freq /= 80;
        div_num = (clk_freq >> bit_num) / freq;
        if(div_num > LEDC_DIV_NUM_HSTIMER0_V) {
            div_num = LEDC_DIV_NUM_HSTIMER0_V;//lowest clock possible
        }
        apb_clk = false;
    } else if(div_num < 256) {
        div_num = 256;//highest clock possible
    }
    _ledcSetupTimer(chan, div_num, bit_num, apb_clk);
    //log_i("Fin: %f, Fclk: %uMhz, bits: %u, DIV: %u, Fout: %f",
    //        freq, apb_clk?80:1, bit_num, div_num, (clk_freq >> bit_num) / (double)div_num);
    return (clk_freq >> bit_num) / (double)div_num;
}