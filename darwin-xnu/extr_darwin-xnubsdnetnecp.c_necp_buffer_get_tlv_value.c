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
 scalar_t__ necp_buffer_get_tlv_length (int /*<<< orphan*/ *,int) ; 

u_int8_t *
necp_buffer_get_tlv_value(u_int8_t *buffer, int tlv_offset, u_int32_t *value_size)
{
	u_int8_t *value = NULL;
	u_int32_t length = necp_buffer_get_tlv_length(buffer, tlv_offset);
	if (length == 0) {
		return (value);
	}

	if (value_size) {
		*value_size = length;
	}

	value = (u_int8_t *)((u_int8_t *)buffer + tlv_offset + sizeof(u_int8_t) + sizeof(u_int32_t));
	return (value);
}