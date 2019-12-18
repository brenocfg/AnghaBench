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
struct niu {int dummy; } ;

/* Variables and functions */
 int bcm8704_init_user_dev3 (struct niu*) ; 
 int bcm8704_reset (struct niu*) ; 
 int xcvr_10g_set_lb_bcm870x (struct niu*) ; 
 int xcvr_diag_bcm870x (struct niu*) ; 

__attribute__((used)) static int xcvr_init_10g_bcm8704(struct niu *np)
{
	int err;

	err = bcm8704_reset(np);
	if (err)
		return err;

	err = bcm8704_init_user_dev3(np);
	if (err)
		return err;

	err = xcvr_10g_set_lb_bcm870x(np);
	if (err)
		return err;

	err =  xcvr_diag_bcm870x(np);
	if (err)
		return err;

	return 0;
}