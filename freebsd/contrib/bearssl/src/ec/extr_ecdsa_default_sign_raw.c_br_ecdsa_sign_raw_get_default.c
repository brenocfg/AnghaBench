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
typedef  int /*<<< orphan*/ * br_ecdsa_sign ;

/* Variables and functions */
 int /*<<< orphan*/  br_ecdsa_i15_sign_raw ; 
 int /*<<< orphan*/  br_ecdsa_i31_sign_raw ; 

br_ecdsa_sign
br_ecdsa_sign_raw_get_default(void)
{
#if BR_LOMUL
	return &br_ecdsa_i15_sign_raw;
#else
	return &br_ecdsa_i31_sign_raw;
#endif
}