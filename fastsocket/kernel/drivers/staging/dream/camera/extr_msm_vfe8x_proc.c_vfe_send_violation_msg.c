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

/* Variables and functions */
 int /*<<< orphan*/  VFE_MSG_ID_VIOLATION ; 
 int /*<<< orphan*/  vfe_send_msg_no_payload (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vfe_send_violation_msg(void)
{
	vfe_send_msg_no_payload(VFE_MSG_ID_VIOLATION);
}