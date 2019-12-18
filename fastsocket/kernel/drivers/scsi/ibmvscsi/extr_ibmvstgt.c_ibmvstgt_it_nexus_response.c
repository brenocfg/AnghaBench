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
typedef  int /*<<< orphan*/  u64 ;
struct vio_port {int /*<<< orphan*/ * rport; } ;
struct srp_target {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eprintk (char*,struct Scsi_Host*,int) ; 
 struct srp_target* host_to_srp_target (struct Scsi_Host*) ; 
 int /*<<< orphan*/  srp_rport_del (int /*<<< orphan*/ *) ; 
 struct vio_port* target_to_port (struct srp_target*) ; 

__attribute__((used)) static int ibmvstgt_it_nexus_response(struct Scsi_Host *shost, u64 itn_id,
				      int result)
{
	struct srp_target *target = host_to_srp_target(shost);
	struct vio_port *vport = target_to_port(target);

	if (result) {
		eprintk("%p %d\n", shost, result);
		srp_rport_del(vport->rport);
		vport->rport = NULL;
	}
	return 0;
}