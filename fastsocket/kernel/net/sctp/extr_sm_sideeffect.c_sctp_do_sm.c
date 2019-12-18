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
struct sctp_endpoint {int dummy; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  sctp_subtype_t ;
typedef  int /*<<< orphan*/  sctp_state_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* fn ) (struct sctp_endpoint*,struct sctp_association*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ sctp_sm_table_entry_t ;
typedef  size_t sctp_event_t ;
typedef  int /*<<< orphan*/  sctp_disposition_t ;
typedef  int /*<<< orphan*/  sctp_cmd_seq_t ;
typedef  int /*<<< orphan*/  printfn_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_POST ; 
 int /*<<< orphan*/  DEBUG_POST_SFX ; 
 int /*<<< orphan*/  DEBUG_PRE ; 
#define  sctp_cname 131 
 int /*<<< orphan*/  sctp_init_cmd_seq (int /*<<< orphan*/ *) ; 
#define  sctp_oname 130 
#define  sctp_pname 129 
 int sctp_side_effects (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_endpoint*,struct sctp_association*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* sctp_sm_lookup_event (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  sctp_tname 128 
 int /*<<< orphan*/  stub2 (struct sctp_endpoint*,struct sctp_association*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

int sctp_do_sm(sctp_event_t event_type, sctp_subtype_t subtype,
	       sctp_state_t state,
	       struct sctp_endpoint *ep,
	       struct sctp_association *asoc,
	       void *event_arg,
	       gfp_t gfp)
{
	sctp_cmd_seq_t commands;
	const sctp_sm_table_entry_t *state_fn;
	sctp_disposition_t status;
	int error = 0;
	typedef const char *(printfn_t)(sctp_subtype_t);

	static printfn_t *table[] = {
		NULL, sctp_cname, sctp_tname, sctp_oname, sctp_pname,
	};
	printfn_t *debug_fn  __attribute__ ((unused)) = table[event_type];

	/* Look up the state function, run it, and then process the
	 * side effects.  These three steps are the heart of lksctp.
	 */
	state_fn = sctp_sm_lookup_event(event_type, state, subtype);

	sctp_init_cmd_seq(&commands);

	DEBUG_PRE;
	status = (*state_fn->fn)(ep, asoc, subtype, event_arg, &commands);
	DEBUG_POST;

	error = sctp_side_effects(event_type, subtype, state,
				  ep, asoc, event_arg, status,
				  &commands, gfp);
	DEBUG_POST_SFX;

	return error;
}