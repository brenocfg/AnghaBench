#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* ccdes_key_set_odd_parity_fn ) (void*,unsigned long) ;} ;

/* Variables and functions */
 TYPE_1__* g_crypto_funcs ; 
 int /*<<< orphan*/  stub1 (void*,unsigned long) ; 

void ccdes_key_set_odd_parity(void *key, unsigned long length)
{
	if (g_crypto_funcs)
		(*g_crypto_funcs->ccdes_key_set_odd_parity_fn)(key, length);
}