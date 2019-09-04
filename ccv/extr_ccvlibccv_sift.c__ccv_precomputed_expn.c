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
 int EXPN_MAX ; 
 int EXPN_SZ ; 
 int _ccv_expn_init ; 
 int /*<<< orphan*/ * _ccv_expn_tab ; 
 int /*<<< orphan*/  exp (double) ; 

__attribute__((used)) static void _ccv_precomputed_expn()
{
	int i;
	for(i = 0; i < EXPN_SZ + 1; i++)
		_ccv_expn_tab[i] = exp(-(double)i * (EXPN_MAX / EXPN_SZ));
	_ccv_expn_init = 1;
}