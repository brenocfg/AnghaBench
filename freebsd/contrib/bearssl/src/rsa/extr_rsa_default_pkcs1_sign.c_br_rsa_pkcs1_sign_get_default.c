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
typedef  int /*<<< orphan*/ * br_rsa_pkcs1_sign ;

/* Variables and functions */
 int /*<<< orphan*/  br_rsa_i15_pkcs1_sign ; 
 int /*<<< orphan*/  br_rsa_i31_pkcs1_sign ; 
 int /*<<< orphan*/  br_rsa_i62_pkcs1_sign ; 

br_rsa_pkcs1_sign
br_rsa_pkcs1_sign_get_default(void)
{
#if BR_INT128 || BR_UMUL128
	return &br_rsa_i62_pkcs1_sign;
#elif BR_LOMUL
	return &br_rsa_i15_pkcs1_sign;
#else
	return &br_rsa_i31_pkcs1_sign;
#endif
}