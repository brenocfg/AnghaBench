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
typedef  scalar_t__ crypto_functions_t ;

/* Variables and functions */
 scalar_t__ g_crypto_funcs ; 

int register_crypto_functions(const crypto_functions_t funcs)
{
	if(g_crypto_funcs)
		return -1;

	g_crypto_funcs = funcs;
	
	return 0;
}