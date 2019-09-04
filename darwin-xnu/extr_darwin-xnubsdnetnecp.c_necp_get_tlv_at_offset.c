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
typedef  int /*<<< orphan*/ * mbuf_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NECPLOG (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  NECPLOG0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int necp_buffer_get_tlv_length (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * necp_buffer_get_tlv_value (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int necp_packet_get_tlv_at_offset (int /*<<< orphan*/ *,int,int,void*,int*) ; 

__attribute__((used)) static int
necp_get_tlv_at_offset(mbuf_t packet, u_int8_t *buffer, u_int32_t buffer_length,
					   int tlv_offset, u_int32_t out_buffer_length, void *out_buffer, u_int32_t *value_size)
{
	if (packet != NULL) {
		// Handle mbuf parsing
		return necp_packet_get_tlv_at_offset(packet, tlv_offset, out_buffer_length, out_buffer, value_size);
	}

	if (buffer == NULL) {
		NECPLOG0(LOG_ERR, "necp_get_tlv_at_offset buffer is NULL");
		return (EINVAL);
	}

	// Handle buffer parsing

	// Validate that buffer has enough room for any TLV
	if (tlv_offset + sizeof(u_int8_t) + sizeof(u_int32_t) > buffer_length) {
		NECPLOG(LOG_ERR, "necp_get_tlv_at_offset buffer_length is too small for TLV (%u < %u)",
				buffer_length, tlv_offset + sizeof(u_int8_t) + sizeof(u_int32_t));
		return (EINVAL);
	}

	// Validate that buffer has enough room for this TLV
	u_int32_t tlv_length = necp_buffer_get_tlv_length(buffer, tlv_offset);
	if (tlv_length > buffer_length - (tlv_offset + sizeof(u_int8_t) + sizeof(u_int32_t))) {
		NECPLOG(LOG_ERR, "necp_get_tlv_at_offset buffer_length is too small for TLV of length %u (%u < %u)",
				tlv_length, buffer_length, tlv_offset + sizeof(u_int8_t) + sizeof(u_int32_t) + tlv_length);
		return (EINVAL);
	}

	if (out_buffer != NULL && out_buffer_length > 0) {
		// Validate that out buffer is large enough for  value
		if (out_buffer_length < tlv_length) {
			NECPLOG(LOG_ERR, "necp_get_tlv_at_offset out_buffer_length is too small for TLV value (%u < %u)",
					out_buffer_length, tlv_length);
			return (EINVAL);
		}

		// Get value pointer
		u_int8_t *tlv_value = necp_buffer_get_tlv_value(buffer, tlv_offset, NULL);
		if (tlv_value == NULL) {
			NECPLOG0(LOG_ERR, "necp_get_tlv_at_offset tlv_value is NULL");
			return (ENOENT);
		}

		// Copy value
		memcpy(out_buffer, tlv_value, tlv_length);
	}

	// Copy out length
	if (value_size != NULL) {
		*value_size = tlv_length;
	}

	return (0);
}