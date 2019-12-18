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
typedef  int /*<<< orphan*/ * br_rsa_keygen ;

/* Variables and functions */
 int /*<<< orphan*/  br_rsa_i15_keygen ; 
 int /*<<< orphan*/  br_rsa_i31_keygen ; 
 int /*<<< orphan*/  br_rsa_i62_keygen ; 

br_rsa_keygen
br_rsa_keygen_get_default(void)
{
#if BR_INT128 || BR_UMUL128
	return &br_rsa_i62_keygen;
#elif BR_LOMUL
	return &br_rsa_i15_keygen;
#else
	return &br_rsa_i31_keygen;
#endif
}