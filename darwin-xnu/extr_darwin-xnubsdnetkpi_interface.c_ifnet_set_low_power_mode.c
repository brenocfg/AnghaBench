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
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  if_set_low_power (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

errno_t
ifnet_set_low_power_mode(ifnet_t ifp, boolean_t on)
{
	errno_t error;

	error = if_set_low_power(ifp, on);

	return (error);
}