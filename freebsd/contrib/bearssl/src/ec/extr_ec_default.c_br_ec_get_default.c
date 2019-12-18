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
typedef  int /*<<< orphan*/  br_ec_impl ;

/* Variables and functions */
 int /*<<< orphan*/  const br_ec_all_m15 ; 
 int /*<<< orphan*/  const br_ec_all_m31 ; 

const br_ec_impl *
br_ec_get_default(void)
{
#if BR_LOMUL
	return &br_ec_all_m15;
#else
	return &br_ec_all_m31;
#endif
}