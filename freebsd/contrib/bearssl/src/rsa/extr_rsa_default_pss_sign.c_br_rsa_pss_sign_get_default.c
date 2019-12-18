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
typedef  int /*<<< orphan*/ * br_rsa_pss_sign ;

/* Variables and functions */
 int /*<<< orphan*/  br_rsa_i15_pss_sign ; 
 int /*<<< orphan*/  br_rsa_i31_pss_sign ; 
 int /*<<< orphan*/  br_rsa_i62_pss_sign ; 

br_rsa_pss_sign
br_rsa_pss_sign_get_default(void)
{
#if BR_INT128 || BR_UMUL128
	return &br_rsa_i62_pss_sign;
#elif BR_LOMUL
	return &br_rsa_i15_pss_sign;
#else
	return &br_rsa_i31_pss_sign;
#endif
}