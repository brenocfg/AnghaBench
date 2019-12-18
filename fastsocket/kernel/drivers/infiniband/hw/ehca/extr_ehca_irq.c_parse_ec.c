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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct ehca_sport {int /*<<< orphan*/  saved_attr; void* port_state; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct ehca_shca {TYPE_1__ ib_device; struct ehca_sport* sport; } ;

/* Variables and functions */
 int EHCA_BMASK_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IB_EVENT_CLIENT_REREGISTER ; 
 int /*<<< orphan*/  IB_EVENT_PORT_ACTIVE ; 
 int /*<<< orphan*/  IB_EVENT_PORT_ERR ; 
 void* IB_PORT_ACTIVE ; 
 void* IB_PORT_DOWN ; 
 int /*<<< orphan*/  NEQE_DISRUPTIVE ; 
 int /*<<< orphan*/  NEQE_EVENT_CODE ; 
 int /*<<< orphan*/  NEQE_PORT_AVAILABILITY ; 
 int /*<<< orphan*/  NEQE_PORT_NUMBER ; 
 int /*<<< orphan*/  NEQE_SPECIFIC_EVENT ; 
 int /*<<< orphan*/  dispatch_port_event (struct ehca_shca*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ehca_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  ehca_nr_ports ; 
 int /*<<< orphan*/  ehca_query_sma_attr (struct ehca_shca*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehca_warn (TYPE_1__*,char*,int,...) ; 
 int /*<<< orphan*/  notify_port_conf_change (struct ehca_shca*,int) ; 
 int /*<<< orphan*/  replay_modify_qp (struct ehca_sport*) ; 

__attribute__((used)) static void parse_ec(struct ehca_shca *shca, u64 eqe)
{
	u8 ec   = EHCA_BMASK_GET(NEQE_EVENT_CODE, eqe);
	u8 port = EHCA_BMASK_GET(NEQE_PORT_NUMBER, eqe);
	u8 spec_event;
	struct ehca_sport *sport = &shca->sport[port - 1];

	switch (ec) {
	case 0x30: /* port availability change */
		if (EHCA_BMASK_GET(NEQE_PORT_AVAILABILITY, eqe)) {
			/* only replay modify_qp calls in autodetect mode;
			 * if AQP1 was destroyed, the port is already down
			 * again and we can drop the event.
			 */
			if (ehca_nr_ports < 0)
				if (replay_modify_qp(sport))
					break;

			sport->port_state = IB_PORT_ACTIVE;
			dispatch_port_event(shca, port, IB_EVENT_PORT_ACTIVE,
					    "is active");
			ehca_query_sma_attr(shca, port, &sport->saved_attr);
		} else {
			sport->port_state = IB_PORT_DOWN;
			dispatch_port_event(shca, port, IB_EVENT_PORT_ERR,
					    "is inactive");
		}
		break;
	case 0x31:
		/* port configuration change
		 * disruptive change is caused by
		 * LID, PKEY or SM change
		 */
		if (EHCA_BMASK_GET(NEQE_DISRUPTIVE, eqe)) {
			ehca_warn(&shca->ib_device, "disruptive port "
				  "%d configuration change", port);

			sport->port_state = IB_PORT_DOWN;
			dispatch_port_event(shca, port, IB_EVENT_PORT_ERR,
					    "is inactive");

			sport->port_state = IB_PORT_ACTIVE;
			dispatch_port_event(shca, port, IB_EVENT_PORT_ACTIVE,
					    "is active");
			ehca_query_sma_attr(shca, port,
					    &sport->saved_attr);
		} else
			notify_port_conf_change(shca, port);
		break;
	case 0x32: /* adapter malfunction */
		ehca_err(&shca->ib_device, "Adapter malfunction.");
		break;
	case 0x33:  /* trace stopped */
		ehca_err(&shca->ib_device, "Traced stopped.");
		break;
	case 0x34: /* util async event */
		spec_event = EHCA_BMASK_GET(NEQE_SPECIFIC_EVENT, eqe);
		if (spec_event == 0x80) /* client reregister required */
			dispatch_port_event(shca, port,
					    IB_EVENT_CLIENT_REREGISTER,
					    "client reregister req.");
		else
			ehca_warn(&shca->ib_device, "Unknown util async "
				  "event %x on port %x", spec_event, port);
		break;
	default:
		ehca_err(&shca->ib_device, "Unknown event code: %x on %s.",
			 ec, shca->ib_device.name);
		break;
	}

	return;
}