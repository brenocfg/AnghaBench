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
 int SSB_CHIPCO_CLK_BASE1 ; 
 int SSB_CHIPCO_CLK_BASE2 ; 
 int SSB_CHIPCO_CLK_F5_BIAS ; 
 int SSB_CHIPCO_CLK_M1 ; 
 int SSB_CHIPCO_CLK_M2 ; 
 int SSB_CHIPCO_CLK_M2_SHIFT ; 
 int SSB_CHIPCO_CLK_M3 ; 
 int SSB_CHIPCO_CLK_M3_SHIFT ; 
 int SSB_CHIPCO_CLK_MC ; 
#define  SSB_CHIPCO_CLK_MC_BYPASS 139 
#define  SSB_CHIPCO_CLK_MC_M1 138 
#define  SSB_CHIPCO_CLK_MC_M1M2 137 
#define  SSB_CHIPCO_CLK_MC_M1M2M3 136 
#define  SSB_CHIPCO_CLK_MC_M1M3 135 
 int SSB_CHIPCO_CLK_MC_SHIFT ; 
 int SSB_CHIPCO_CLK_N1 ; 
 int SSB_CHIPCO_CLK_N2 ; 
 int SSB_CHIPCO_CLK_N2_SHIFT ; 
 int SSB_CHIPCO_CLK_T2M2_BIAS ; 
 int SSB_CHIPCO_CLK_T2MC_M1BYP ; 
 int SSB_CHIPCO_CLK_T2MC_M2BYP ; 
 int SSB_CHIPCO_CLK_T2MC_M3BYP ; 
 int SSB_CHIPCO_CLK_T2_BIAS ; 
 int SSB_CHIPCO_CLK_T6_M0 ; 
 int SSB_CHIPCO_CLK_T6_M1 ; 
 int SSB_CHIPCO_CLK_T6_MMASK ; 
#define  SSB_PLLTYPE_1 134 
#define  SSB_PLLTYPE_2 133 
#define  SSB_PLLTYPE_3 132 
#define  SSB_PLLTYPE_4 131 
#define  SSB_PLLTYPE_5 130 
#define  SSB_PLLTYPE_6 129 
#define  SSB_PLLTYPE_7 128 
 int /*<<< orphan*/  SSB_WARN_ON (int) ; 
 int clkfactor_f6_resolve (int) ; 

u32 ssb_calc_clock_rate(u32 plltype, u32 n, u32 m)
{
	u32 n1, n2, clock, m1, m2, m3, mc;

	n1 = (n & SSB_CHIPCO_CLK_N1);
	n2 = ((n & SSB_CHIPCO_CLK_N2) >> SSB_CHIPCO_CLK_N2_SHIFT);

	switch (plltype) {
	case SSB_PLLTYPE_6: /* 100/200 or 120/240 only */
		if (m & SSB_CHIPCO_CLK_T6_MMASK)
			return SSB_CHIPCO_CLK_T6_M1;
		return SSB_CHIPCO_CLK_T6_M0;
	case SSB_PLLTYPE_1: /* 48Mhz base, 3 dividers */
	case SSB_PLLTYPE_3: /* 25Mhz, 2 dividers */
	case SSB_PLLTYPE_4: /* 48Mhz, 4 dividers */
	case SSB_PLLTYPE_7: /* 25Mhz, 4 dividers */
		n1 = clkfactor_f6_resolve(n1);
		n2 += SSB_CHIPCO_CLK_F5_BIAS;
		break;
	case SSB_PLLTYPE_2: /* 48Mhz, 4 dividers */
		n1 += SSB_CHIPCO_CLK_T2_BIAS;
		n2 += SSB_CHIPCO_CLK_T2_BIAS;
		SSB_WARN_ON(!((n1 >= 2) && (n1 <= 7)));
		SSB_WARN_ON(!((n2 >= 5) && (n2 <= 23)));
		break;
	case SSB_PLLTYPE_5: /* 25Mhz, 4 dividers */
		return 100000000;
	default:
		SSB_WARN_ON(1);
	}

	switch (plltype) {
	case SSB_PLLTYPE_3: /* 25Mhz, 2 dividers */
	case SSB_PLLTYPE_7: /* 25Mhz, 4 dividers */
		clock = SSB_CHIPCO_CLK_BASE2 * n1 * n2;
		break;
	default:
		clock = SSB_CHIPCO_CLK_BASE1 * n1 * n2;
	}
	if (!clock)
		return 0;

	m1 = (m & SSB_CHIPCO_CLK_M1);
	m2 = ((m & SSB_CHIPCO_CLK_M2) >> SSB_CHIPCO_CLK_M2_SHIFT);
	m3 = ((m & SSB_CHIPCO_CLK_M3) >> SSB_CHIPCO_CLK_M3_SHIFT);
	mc = ((m & SSB_CHIPCO_CLK_MC) >> SSB_CHIPCO_CLK_MC_SHIFT);

	switch (plltype) {
	case SSB_PLLTYPE_1: /* 48Mhz base, 3 dividers */
	case SSB_PLLTYPE_3: /* 25Mhz, 2 dividers */
	case SSB_PLLTYPE_4: /* 48Mhz, 4 dividers */
	case SSB_PLLTYPE_7: /* 25Mhz, 4 dividers */
		m1 = clkfactor_f6_resolve(m1);
		if ((plltype == SSB_PLLTYPE_1) ||
		    (plltype == SSB_PLLTYPE_3))
			m2 += SSB_CHIPCO_CLK_F5_BIAS;
		else
			m2 = clkfactor_f6_resolve(m2);
		m3 = clkfactor_f6_resolve(m3);

		switch (mc) {
		case SSB_CHIPCO_CLK_MC_BYPASS:
			return clock;
		case SSB_CHIPCO_CLK_MC_M1:
			return (clock / m1);
		case SSB_CHIPCO_CLK_MC_M1M2:
			return (clock / (m1 * m2));
		case SSB_CHIPCO_CLK_MC_M1M2M3:
			return (clock / (m1 * m2 * m3));
		case SSB_CHIPCO_CLK_MC_M1M3:
			return (clock / (m1 * m3));
		}
		return 0;
	case SSB_PLLTYPE_2:
		m1 += SSB_CHIPCO_CLK_T2_BIAS;
		m2 += SSB_CHIPCO_CLK_T2M2_BIAS;
		m3 += SSB_CHIPCO_CLK_T2_BIAS;
		SSB_WARN_ON(!((m1 >= 2) && (m1 <= 7)));
		SSB_WARN_ON(!((m2 >= 3) && (m2 <= 10)));
		SSB_WARN_ON(!((m3 >= 2) && (m3 <= 7)));

		if (!(mc & SSB_CHIPCO_CLK_T2MC_M1BYP))
			clock /= m1;
		if (!(mc & SSB_CHIPCO_CLK_T2MC_M2BYP))
			clock /= m2;
		if (!(mc & SSB_CHIPCO_CLK_T2MC_M3BYP))
			clock /= m3;
		return clock;
	default:
		SSB_WARN_ON(1);
	}
	return 0;
}