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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  scalar_t__ u_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DATA_EOR ; 
 int EINVAL ; 
 int ctl_enqueuedata (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * netagent_kctlref ; 

__attribute__((used)) static int
netagent_send_ctl_data(u_int32_t control_unit, u_int8_t *buffer, size_t buffer_size)
{
	if (netagent_kctlref == NULL || control_unit == 0 || buffer == NULL || buffer_size == 0) {
		return (EINVAL);
	}

	return ctl_enqueuedata(netagent_kctlref, control_unit, buffer, buffer_size, CTL_DATA_EOR);
}