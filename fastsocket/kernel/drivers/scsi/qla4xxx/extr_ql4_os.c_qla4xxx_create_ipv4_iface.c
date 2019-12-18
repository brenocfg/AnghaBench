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
struct scsi_qla_host {scalar_t__ iface_ipv4; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_IFACE_TYPE_IPV4 ; 
 int /*<<< orphan*/  KERN_ERR ; 
 scalar_t__ iscsi_create_iface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*) ; 
 int /*<<< orphan*/  qla4xxx_iscsi_transport ; 

__attribute__((used)) static void qla4xxx_create_ipv4_iface(struct scsi_qla_host *ha)
{
	if (ha->iface_ipv4)
		return;

	/* IPv4 */
	ha->iface_ipv4 = iscsi_create_iface(ha->host,
					    &qla4xxx_iscsi_transport,
					    ISCSI_IFACE_TYPE_IPV4, 0, 0);
	if (!ha->iface_ipv4)
		ql4_printk(KERN_ERR, ha, "Could not create IPv4 iSCSI "
			   "iface0.\n");
}