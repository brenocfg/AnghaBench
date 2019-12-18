#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  initial_tsn; int /*<<< orphan*/  sinit_max_instreams; int /*<<< orphan*/  sinit_num_ostreams; int /*<<< orphan*/  peer_vtag; int /*<<< orphan*/  peer_ttag; int /*<<< orphan*/  my_vtag; int /*<<< orphan*/  my_ttag; } ;
struct sctp_association {int state; TYPE_1__ c; int /*<<< orphan*/  rwnd; } ;

/* Variables and functions */
#define  SCTP_STATE_COOKIE_ECHOED 129 
#define  SCTP_STATE_COOKIE_WAIT 128 

__attribute__((used)) static void sctp_tietags_populate(struct sctp_association *new_asoc,
				  const struct sctp_association *asoc)
{
	switch (asoc->state) {

	/* 5.2.1 INIT received in COOKIE-WAIT or COOKIE-ECHOED State */

	case SCTP_STATE_COOKIE_WAIT:
		new_asoc->c.my_vtag     = asoc->c.my_vtag;
		new_asoc->c.my_ttag     = asoc->c.my_vtag;
		new_asoc->c.peer_ttag   = 0;
		break;

	case SCTP_STATE_COOKIE_ECHOED:
		new_asoc->c.my_vtag     = asoc->c.my_vtag;
		new_asoc->c.my_ttag     = asoc->c.my_vtag;
		new_asoc->c.peer_ttag   = asoc->c.peer_vtag;
		break;

	/* 5.2.2 Unexpected INIT in States Other than CLOSED, COOKIE-ECHOED,
	 * COOKIE-WAIT and SHUTDOWN-ACK-SENT
	 */
	default:
		new_asoc->c.my_ttag   = asoc->c.my_vtag;
		new_asoc->c.peer_ttag = asoc->c.peer_vtag;
		break;
	}

	/* Other parameters for the endpoint SHOULD be copied from the
	 * existing parameters of the association (e.g. number of
	 * outbound streams) into the INIT ACK and cookie.
	 */
	new_asoc->rwnd                  = asoc->rwnd;
	new_asoc->c.sinit_num_ostreams  = asoc->c.sinit_num_ostreams;
	new_asoc->c.sinit_max_instreams = asoc->c.sinit_max_instreams;
	new_asoc->c.initial_tsn         = asoc->c.initial_tsn;
}