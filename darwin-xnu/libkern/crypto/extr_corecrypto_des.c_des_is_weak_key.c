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
typedef  int /*<<< orphan*/  des_cblock ;
struct TYPE_2__ {int (* ccdes_key_is_weak_fn ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CCDES_KEY_SIZE ; 
 TYPE_1__* g_crypto_funcs ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int des_is_weak_key(des_cblock *key)
{
	return g_crypto_funcs->ccdes_key_is_weak_fn(key, CCDES_KEY_SIZE);
}