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
typedef  size_t sctp_state_t ;
typedef  int /*<<< orphan*/  sctp_sm_table_entry_t ;
typedef  size_t sctp_cid_t ;

/* Variables and functions */
 size_t SCTP_CID_ASCONF ; 
 size_t SCTP_CID_ASCONF_ACK ; 
 size_t SCTP_CID_AUTH ; 
 size_t SCTP_CID_BASE_MAX ; 
 size_t SCTP_CID_FWD_TSN ; 
 size_t SCTP_STATE_MAX ; 
 int /*<<< orphan*/  const** addip_chunk_event_table ; 
 int /*<<< orphan*/  const** auth_chunk_event_table ; 
 int /*<<< orphan*/  const bug ; 
 int /*<<< orphan*/  const** chunk_event_table ; 
 int /*<<< orphan*/  const* chunk_event_table_unknown ; 
 int /*<<< orphan*/  const** prsctp_chunk_event_table ; 
 scalar_t__ sctp_addip_enable ; 
 scalar_t__ sctp_auth_enable ; 
 scalar_t__ sctp_prsctp_enable ; 

__attribute__((used)) static const sctp_sm_table_entry_t *sctp_chunk_event_lookup(sctp_cid_t cid,
							    sctp_state_t state)
{
	if (state > SCTP_STATE_MAX)
		return &bug;

	if (cid <= SCTP_CID_BASE_MAX)
		return &chunk_event_table[cid][state];

	if (sctp_prsctp_enable) {
		if (cid == SCTP_CID_FWD_TSN)
			return &prsctp_chunk_event_table[0][state];
	}

	if (sctp_addip_enable) {
		if (cid == SCTP_CID_ASCONF)
			return &addip_chunk_event_table[0][state];

		if (cid == SCTP_CID_ASCONF_ACK)
			return &addip_chunk_event_table[1][state];
	}

	if (sctp_auth_enable) {
		if (cid == SCTP_CID_AUTH)
			return &auth_chunk_event_table[0][state];
	}

	return &chunk_event_table_unknown[state];
}