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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/ * mbuf_t ;

/* Variables and functions */
 int necp_buffer_find_tlv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int necp_packet_find_tlv (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int
necp_find_tlv(mbuf_t packet, u_int8_t *buffer, u_int32_t buffer_length, int offset, u_int8_t type, int *err, int next)
{
	int cursor = -1;
	if (packet != NULL) {
		cursor = necp_packet_find_tlv(packet, offset, type, err, next);
	} else if (buffer != NULL) {
		cursor = necp_buffer_find_tlv(buffer, buffer_length, offset, type, next);
	}
	return (cursor);
}