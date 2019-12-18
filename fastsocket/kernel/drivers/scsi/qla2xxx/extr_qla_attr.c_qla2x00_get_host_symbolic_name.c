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
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  fc_host_symbolic_name (struct Scsi_Host*) ; 
 int /*<<< orphan*/  qla2x00_get_sym_node_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static void
qla2x00_get_host_symbolic_name(struct Scsi_Host *shost)
{
	scsi_qla_host_t *vha = shost_priv(shost);

	qla2x00_get_sym_node_name(vha, fc_host_symbolic_name(shost));
}