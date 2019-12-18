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

/* Variables and functions */
 int SAB_BASE_BAUD ; 

__attribute__((used)) static void calc_ebrg(int baud, int *n_ret, int *m_ret)
{
	int	n, m;

	if (baud == 0) {
		*n_ret = 0;
		*m_ret = 0;
		return;
	}
     
	/*
	 * We scale numbers by 10 so that we get better accuracy
	 * without having to use floating point.  Here we increment m
	 * until n is within the valid range.
	 */
	n = (SAB_BASE_BAUD * 10) / baud;
	m = 0;
	while (n >= 640) {
		n = n / 2;
		m++;
	}
	n = (n+5) / 10;
	/*
	 * We try very hard to avoid speeds with M == 0 since they may
	 * not work correctly for XTAL frequences above 10 MHz.
	 */
	if ((m == 0) && ((n & 1) == 0)) {
		n = n / 2;
		m++;
	}
	*n_ret = n - 1;
	*m_ret = m;
}