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

/* Variables and functions */

u_int8_t
necp_buffer_get_tlv_type(u_int8_t *buffer, int tlv_offset)
{
	u_int8_t *type = NULL;

	if (buffer == NULL) {
		return (0);
	}

	type = (u_int8_t *)((u_int8_t *)buffer + tlv_offset);
	return (type ? *type : 0);
}