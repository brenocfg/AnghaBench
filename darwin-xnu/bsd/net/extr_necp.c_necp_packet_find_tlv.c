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
typedef  scalar_t__ u_int8_t ;
typedef  scalar_t__ u_int32_t ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int /*<<< orphan*/  curr_type ;
typedef  int /*<<< orphan*/  curr_length ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ NECP_TLV_NIL ; 
 int mbuf_copydata (int /*<<< orphan*/ ,size_t,int,scalar_t__*) ; 

__attribute__((used)) static int
necp_packet_find_tlv(mbuf_t packet, int offset, u_int8_t type, int *err, int next)
{
	size_t	cursor			= offset;
	int		error			= 0;
	u_int32_t	curr_length;
	u_int8_t	curr_type;

	*err = 0;

	do {
		if (!next) {
			error = mbuf_copydata(packet, cursor, sizeof(curr_type), &curr_type);
			if (error) {
				*err = ENOENT;
				return (-1);
			}
		} else {
			next = 0;
			curr_type = NECP_TLV_NIL;
		}

		if (curr_type != type) {
			cursor += sizeof(curr_type);
			error = mbuf_copydata(packet, cursor, sizeof(curr_length), &curr_length);
			if (error) {
				*err = error;
				return (-1);
			}
			cursor += (sizeof(curr_length) + curr_length);
		}
	} while (curr_type != type);

	return (cursor);
}