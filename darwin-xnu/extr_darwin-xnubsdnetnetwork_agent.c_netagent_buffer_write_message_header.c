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
typedef  void* u_int8_t ;
typedef  void* u_int32_t ;
struct netagent_message_header {void* message_payload_length; void* message_error; void* message_id; void* message_flags; void* message_type; } ;

/* Variables and functions */

__attribute__((used)) static u_int8_t *
netagent_buffer_write_message_header(u_int8_t *buffer, u_int8_t message_type, u_int8_t flags,
									 u_int32_t message_id, u_int32_t error, u_int32_t payload_length)
{
	((struct netagent_message_header *)(void *)buffer)->message_type = message_type;
	((struct netagent_message_header *)(void *)buffer)->message_flags = flags;
	((struct netagent_message_header *)(void *)buffer)->message_id = message_id;
	((struct netagent_message_header *)(void *)buffer)->message_error = error;
	((struct netagent_message_header *)(void *)buffer)->message_payload_length = payload_length;
	return (buffer + sizeof(struct netagent_message_header));
}