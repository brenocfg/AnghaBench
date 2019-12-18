#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  chunk; } ;
typedef  TYPE_1__ sctp_subtype_t ;
typedef  int /*<<< orphan*/  sctp_state_t ;
typedef  int /*<<< orphan*/  sctp_sm_table_entry_t ;
typedef  int sctp_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  DO_LOOKUP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_EVENT_OTHER_MAX ; 
 int /*<<< orphan*/  SCTP_EVENT_PRIMITIVE_MAX ; 
 int /*<<< orphan*/  SCTP_EVENT_TIMEOUT_MAX ; 
#define  SCTP_EVENT_T_CHUNK 131 
#define  SCTP_EVENT_T_OTHER 130 
#define  SCTP_EVENT_T_PRIMITIVE 129 
#define  SCTP_EVENT_T_TIMEOUT 128 
 int /*<<< orphan*/  const bug ; 
 int /*<<< orphan*/  other ; 
 int /*<<< orphan*/  other_event_table ; 
 int /*<<< orphan*/  primitive ; 
 int /*<<< orphan*/  primitive_event_table ; 
 int /*<<< orphan*/  const* sctp_chunk_event_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  timeout_event_table ; 

const sctp_sm_table_entry_t *sctp_sm_lookup_event(sctp_event_t event_type,
						  sctp_state_t state,
						  sctp_subtype_t event_subtype)
{
	switch (event_type) {
	case SCTP_EVENT_T_CHUNK:
		return sctp_chunk_event_lookup(event_subtype.chunk, state);
		break;
	case SCTP_EVENT_T_TIMEOUT:
		DO_LOOKUP(SCTP_EVENT_TIMEOUT_MAX, timeout,
			  timeout_event_table);
		break;

	case SCTP_EVENT_T_OTHER:
		DO_LOOKUP(SCTP_EVENT_OTHER_MAX, other, other_event_table);
		break;

	case SCTP_EVENT_T_PRIMITIVE:
		DO_LOOKUP(SCTP_EVENT_PRIMITIVE_MAX, primitive,
			  primitive_event_table);
		break;

	default:
		/* Yikes!  We got an illegal event type.  */
		return &bug;
	}
}