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
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  type ;
typedef  int /*<<< orphan*/  length ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 
 int /*<<< orphan*/  necp_buffer_write_tlv_validate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

u_int8_t *
necp_buffer_write_tlv(u_int8_t *cursor, u_int8_t type,
					  u_int32_t length, const void *value,
					  u_int8_t *buffer, u_int32_t buffer_length)
{
	if (!necp_buffer_write_tlv_validate(cursor, type, length, buffer, buffer_length)) {
		return (NULL);
	}
	u_int8_t *next_tlv = (u_int8_t *)(cursor + sizeof(type) + sizeof(length) + length);
	*(u_int8_t *)(cursor) = type;
	*(u_int32_t *)(void *)(cursor + sizeof(type)) = length;
	if (length > 0) {
		memcpy((u_int8_t *)(cursor + sizeof(type) + sizeof(length)), value, length);
	}

	return (next_tlv);
}