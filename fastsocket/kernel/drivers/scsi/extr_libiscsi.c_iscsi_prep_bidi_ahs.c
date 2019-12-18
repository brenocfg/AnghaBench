#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int dummy; } ;
struct iscsi_task {TYPE_1__* conn; struct scsi_cmnd* sc; } ;
struct iscsi_rlength_ahdr {int /*<<< orphan*/  ahslength; int /*<<< orphan*/  read_length; scalar_t__ reserved; int /*<<< orphan*/  ahstype; } ;
struct TYPE_4__ {int /*<<< orphan*/  length; } ;
struct TYPE_3__ {int /*<<< orphan*/  session; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_AHSTYPE_RLENGTH ; 
 int /*<<< orphan*/  ISCSI_DBG_SESSION (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int iscsi_add_hdr (struct iscsi_task*,int) ; 
 struct iscsi_rlength_ahdr* iscsi_next_hdr (struct iscsi_task*) ; 
 TYPE_2__* scsi_in (struct scsi_cmnd*) ; 

__attribute__((used)) static int iscsi_prep_bidi_ahs(struct iscsi_task *task)
{
	struct scsi_cmnd *sc = task->sc;
	struct iscsi_rlength_ahdr *rlen_ahdr;
	int rc;

	rlen_ahdr = iscsi_next_hdr(task);
	rc = iscsi_add_hdr(task, sizeof(*rlen_ahdr));
	if (rc)
		return rc;

	rlen_ahdr->ahslength =
		cpu_to_be16(sizeof(rlen_ahdr->read_length) +
						  sizeof(rlen_ahdr->reserved));
	rlen_ahdr->ahstype = ISCSI_AHSTYPE_RLENGTH;
	rlen_ahdr->reserved = 0;
	rlen_ahdr->read_length = cpu_to_be32(scsi_in(sc)->length);

	ISCSI_DBG_SESSION(task->conn->session,
			  "bidi-in rlen_ahdr->read_length(%d) "
		          "rlen_ahdr->ahslength(%d)\n",
		          be32_to_cpu(rlen_ahdr->read_length),
		          be16_to_cpu(rlen_ahdr->ahslength));
	return 0;
}