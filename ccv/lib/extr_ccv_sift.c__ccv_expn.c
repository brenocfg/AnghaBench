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
 double EXPN_MAX ; 
 double EXPN_SZ ; 
 double* _ccv_expn_tab ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline double _ccv_expn(double x)
{
	double a, b, r;
	int i;
	assert(0 <= x && x <= EXPN_MAX);
	if (x > EXPN_MAX)
		return 0.0;
	x *= EXPN_SZ / EXPN_MAX;
	i = (int)x;
	r = x - i;
	a = _ccv_expn_tab[i];
	b = _ccv_expn_tab[i + 1];
	return a + r * (b - a);
}