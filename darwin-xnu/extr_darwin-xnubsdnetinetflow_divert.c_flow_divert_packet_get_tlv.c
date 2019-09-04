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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  type ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int /*<<< orphan*/  length ;

/* Variables and functions */
 int flow_divert_packet_find_tlv (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int mbuf_copydata (int /*<<< orphan*/ ,int,size_t,void*) ; 
 size_t ntohl (size_t) ; 

__attribute__((used)) static int
flow_divert_packet_get_tlv(mbuf_t packet, int offset, uint8_t type, size_t buff_len, void *buff, uint32_t *val_size)
{
	int			error		= 0;
	uint32_t	length;
	int			tlv_offset;

	tlv_offset = flow_divert_packet_find_tlv(packet, offset, type, &error, 0);
	if (tlv_offset < 0) {
		return error;
	}

	error = mbuf_copydata(packet, tlv_offset + sizeof(type), sizeof(length), &length);
	if (error) {
		return error;
	}

	length = ntohl(length);

	if (val_size != NULL) {
		*val_size = length;
	}

	if (buff != NULL && buff_len > 0) {
		size_t to_copy = (length < buff_len) ? length : buff_len;
		error = mbuf_copydata(packet, tlv_offset + sizeof(type) + sizeof(length), to_copy, buff);
		if (error) {
			return error;
		}
	}

	return 0;
}