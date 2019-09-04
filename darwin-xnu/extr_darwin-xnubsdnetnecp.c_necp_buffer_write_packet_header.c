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
typedef  int /*<<< orphan*/  u_int32_t ;
struct necp_packet_header {int /*<<< orphan*/  message_id; void* flags; void* packet_type; } ;

/* Variables and functions */

__attribute__((used)) static u_int8_t *
necp_buffer_write_packet_header(u_int8_t *buffer, u_int8_t packet_type, u_int8_t flags, u_int32_t message_id)
{
	((struct necp_packet_header *)(void *)buffer)->packet_type = packet_type;
	((struct necp_packet_header *)(void *)buffer)->flags = flags;
	((struct necp_packet_header *)(void *)buffer)->message_id = message_id;
	return (buffer + sizeof(struct necp_packet_header));
}