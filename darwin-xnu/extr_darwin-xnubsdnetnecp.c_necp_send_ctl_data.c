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
struct necp_session {int /*<<< orphan*/  control_unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DATA_EOR ; 
 int FALSE ; 
 int ctl_enqueuedata (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * necp_kctlref ; 

__attribute__((used)) static bool
necp_send_ctl_data(struct necp_session *session, u_int8_t *buffer, size_t buffer_size)
{
	int		error;

	if (necp_kctlref == NULL || session == NULL || buffer == NULL || buffer_size == 0) {
		return (FALSE);
	}

	error = ctl_enqueuedata(necp_kctlref, session->control_unit, buffer, buffer_size, CTL_DATA_EOR);

	return (error == 0);
}