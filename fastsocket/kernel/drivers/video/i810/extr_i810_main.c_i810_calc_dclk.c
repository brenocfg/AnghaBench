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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static void i810_calc_dclk(u32 freq, u32 *m, u32 *n, u32 *p)
{
	u32 m_reg, n_reg, p_divisor, n_target_max;
	u32 m_target, n_target, p_target, n_best, m_best, mod;
	u32 f_out, target_freq, diff = 0, mod_min, diff_min;

	diff_min = mod_min = 0xFFFFFFFF;
	n_best = m_best = m_target = f_out = 0;

	target_freq =  freq;
	n_target_max = 30;

	/*
	 * find P such that target freq is 16x reference freq (Hz). 
	 */
	p_divisor = 1;
	p_target = 0;
	while(!((1000000 * p_divisor)/(16 * 24 * target_freq)) && 
	      p_divisor <= 32) {
		p_divisor <<= 1;
		p_target++;
	}

	n_reg = m_reg = n_target = 3;	
	while (diff_min && mod_min && (n_target < n_target_max)) {
		f_out = (p_divisor * n_reg * 1000000)/(4 * 24 * m_reg);
		mod = (p_divisor * n_reg * 1000000) % (4 * 24 * m_reg);
		m_target = m_reg;
		n_target = n_reg;
		if (f_out <= target_freq) {
			n_reg++;
			diff = target_freq - f_out;
		} else {
			m_reg++;
			diff = f_out - target_freq;
		}

		if (diff_min > diff) {
			diff_min = diff;
			n_best = n_target;
			m_best = m_target;
		}		 

		if (!diff && mod_min > mod) {
			mod_min = mod;
			n_best = n_target;
			m_best = m_target;
		}
	} 
	if (m) *m = (m_best - 2) & 0x3FF;
	if (n) *n = (n_best - 2) & 0x3FF;
	if (p) *p = (p_target << 4);
}