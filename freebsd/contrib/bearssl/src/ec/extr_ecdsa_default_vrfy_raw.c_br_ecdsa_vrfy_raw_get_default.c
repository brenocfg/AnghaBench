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
typedef  int /*<<< orphan*/ * br_ecdsa_vrfy ;

/* Variables and functions */
 int /*<<< orphan*/  br_ecdsa_i15_vrfy_raw ; 
 int /*<<< orphan*/  br_ecdsa_i31_vrfy_raw ; 

br_ecdsa_vrfy
br_ecdsa_vrfy_raw_get_default(void)
{
#if BR_LOMUL
	return &br_ecdsa_i15_vrfy_raw;
#else
	return &br_ecdsa_i31_vrfy_raw;
#endif
}