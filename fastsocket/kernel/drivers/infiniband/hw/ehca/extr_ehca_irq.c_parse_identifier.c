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
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct ehca_shca {TYPE_1__ ib_device; } ;

/* Variables and functions */
 int EHCA_BMASK_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EQE_EE_IDENTIFIER ; 
 int /*<<< orphan*/  IB_EVENT_COMM_EST ; 
 int /*<<< orphan*/  IB_EVENT_PATH_MIG ; 
 int /*<<< orphan*/  IB_EVENT_QP_FATAL ; 
 int /*<<< orphan*/  IB_EVENT_SQ_DRAINED ; 
 int /*<<< orphan*/  IB_EVENT_SRQ_LIMIT_REACHED ; 
 int /*<<< orphan*/  cq_event_callback (struct ehca_shca*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehca_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  ehca_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  qp_event_callback (struct ehca_shca*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void parse_identifier(struct ehca_shca *shca, u64 eqe)
{
	u8 identifier = EHCA_BMASK_GET(EQE_EE_IDENTIFIER, eqe);

	switch (identifier) {
	case 0x02: /* path migrated */
		qp_event_callback(shca, eqe, IB_EVENT_PATH_MIG, 0);
		break;
	case 0x03: /* communication established */
		qp_event_callback(shca, eqe, IB_EVENT_COMM_EST, 0);
		break;
	case 0x04: /* send queue drained */
		qp_event_callback(shca, eqe, IB_EVENT_SQ_DRAINED, 0);
		break;
	case 0x05: /* QP error */
	case 0x06: /* QP error */
		qp_event_callback(shca, eqe, IB_EVENT_QP_FATAL, 1);
		break;
	case 0x07: /* CQ error */
	case 0x08: /* CQ error */
		cq_event_callback(shca, eqe);
		break;
	case 0x09: /* MRMWPTE error */
		ehca_err(&shca->ib_device, "MRMWPTE error.");
		break;
	case 0x0A: /* port event */
		ehca_err(&shca->ib_device, "Port event.");
		break;
	case 0x0B: /* MR access error */
		ehca_err(&shca->ib_device, "MR access error.");
		break;
	case 0x0C: /* EQ error */
		ehca_err(&shca->ib_device, "EQ error.");
		break;
	case 0x0D: /* P/Q_Key mismatch */
		ehca_err(&shca->ib_device, "P/Q_Key mismatch.");
		break;
	case 0x10: /* sampling complete */
		ehca_err(&shca->ib_device, "Sampling complete.");
		break;
	case 0x11: /* unaffiliated access error */
		ehca_err(&shca->ib_device, "Unaffiliated access error.");
		break;
	case 0x12: /* path migrating */
		ehca_err(&shca->ib_device, "Path migrating.");
		break;
	case 0x13: /* interface trace stopped */
		ehca_err(&shca->ib_device, "Interface trace stopped.");
		break;
	case 0x14: /* first error capture info available */
		ehca_info(&shca->ib_device, "First error capture available");
		break;
	case 0x15: /* SRQ limit reached */
		qp_event_callback(shca, eqe, IB_EVENT_SRQ_LIMIT_REACHED, 0);
		break;
	default:
		ehca_err(&shca->ib_device, "Unknown identifier: %x on %s.",
			 identifier, shca->ib_device.name);
		break;
	}

	return;
}