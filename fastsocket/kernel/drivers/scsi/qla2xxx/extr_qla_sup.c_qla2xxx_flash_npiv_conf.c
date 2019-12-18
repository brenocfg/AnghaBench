#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vid ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct qla_npiv_header {scalar_t__ version; scalar_t__ entries; scalar_t__ checksum; } ;
struct qla_npiv_entry {scalar_t__ flags; scalar_t__ vf_id; int /*<<< orphan*/  f_qos; int /*<<< orphan*/  q_qos; int /*<<< orphan*/  node_name; int /*<<< orphan*/  port_name; } ;
struct TYPE_9__ {scalar_t__ nic_core_reset_hdlr_active; } ;
struct qla_hw_data {int flt_region_npiv_conf; int /*<<< orphan*/ * npiv_info; TYPE_2__* isp_ops; TYPE_1__ flags; } ;
struct fc_vport_identifiers {int disable; void* node_name; void* port_name; int /*<<< orphan*/  vport_type; int /*<<< orphan*/  roles; } ;
struct fc_vport {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  host; struct qla_hw_data* hw; } ;
typedef  TYPE_3__ scsi_qla_host_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* read_optrom ) (TYPE_3__*,int /*<<< orphan*/ *,int,int) ;} ;

/* Variables and functions */
 int BIT_0 ; 
 int /*<<< orphan*/  FC_PORTTYPE_NPIV ; 
 int /*<<< orphan*/  FC_PORT_ROLE_FCP_INITIATOR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_CNA_CAPABLE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA2031 (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA24XX_TYPE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA25XX (struct qla_hw_data*) ; 
 int NPIV_CONFIG_SIZE ; 
 int QLA_PRECONFIG_VPORTS ; 
 scalar_t__ __constant_cpu_to_le16 (int) ; 
 struct fc_vport* fc_vport_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fc_vport_identifiers*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct qla_npiv_entry*,int) ; 
 int /*<<< orphan*/  memset (struct fc_vport_identifiers*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_3__*,int,char*,int,unsigned long long,unsigned long long,...) ; 
 int /*<<< orphan*/  ql_dbg_user ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_3__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ *,int,int) ; 
 void* wwn_to_u64 (int /*<<< orphan*/ ) ; 

void
qla2xxx_flash_npiv_conf(scsi_qla_host_t *vha)
{
#define NPIV_CONFIG_SIZE	(16*1024)
	void *data;
	uint16_t *wptr;
	uint16_t cnt, chksum;
	int i;
	struct qla_npiv_header hdr;
	struct qla_npiv_entry *entry;
	struct qla_hw_data *ha = vha->hw;

	if (!IS_QLA24XX_TYPE(ha) && !IS_QLA25XX(ha) &&
	    !IS_CNA_CAPABLE(ha) && !IS_QLA2031(ha))
		return;

	if (ha->flags.nic_core_reset_hdlr_active)
		return;

	ha->isp_ops->read_optrom(vha, (uint8_t *)&hdr,
	    ha->flt_region_npiv_conf << 2, sizeof(struct qla_npiv_header));
	if (hdr.version == __constant_cpu_to_le16(0xffff))
		return;
	if (hdr.version != __constant_cpu_to_le16(1)) {
		ql_dbg(ql_dbg_user, vha, 0x7090,
		    "Unsupported NPIV-Config "
		    "detected: version=0x%x entries=0x%x checksum=0x%x.\n",
		    le16_to_cpu(hdr.version), le16_to_cpu(hdr.entries),
		    le16_to_cpu(hdr.checksum));
		return;
	}

	data = kmalloc(NPIV_CONFIG_SIZE, GFP_KERNEL);
	if (!data) {
		ql_log(ql_log_warn, vha, 0x7091,
		    "Unable to allocate memory for data.\n");
		return;
	}

	ha->isp_ops->read_optrom(vha, (uint8_t *)data,
	    ha->flt_region_npiv_conf << 2, NPIV_CONFIG_SIZE);

	cnt = (sizeof(struct qla_npiv_header) + le16_to_cpu(hdr.entries) *
	    sizeof(struct qla_npiv_entry)) >> 1;
	for (wptr = data, chksum = 0; cnt; cnt--)
		chksum += le16_to_cpu(*wptr++);
	if (chksum) {
		ql_dbg(ql_dbg_user, vha, 0x7092,
		    "Inconsistent NPIV-Config "
		    "detected: version=0x%x entries=0x%x checksum=0x%x.\n",
		    le16_to_cpu(hdr.version), le16_to_cpu(hdr.entries),
		    le16_to_cpu(hdr.checksum));
		goto done;
	}

	entry = data + sizeof(struct qla_npiv_header);
	cnt = le16_to_cpu(hdr.entries);
	for (i = 0; cnt; cnt--, entry++, i++) {
		uint16_t flags;
		struct fc_vport_identifiers vid;
		struct fc_vport *vport;

		memcpy(&ha->npiv_info[i], entry, sizeof(struct qla_npiv_entry));

		flags = le16_to_cpu(entry->flags);
		if (flags == 0xffff)
			continue;
		if ((flags & BIT_0) == 0)
			continue;

		memset(&vid, 0, sizeof(vid));
		vid.roles = FC_PORT_ROLE_FCP_INITIATOR;
		vid.vport_type = FC_PORTTYPE_NPIV;
		vid.disable = false;
		vid.port_name = wwn_to_u64(entry->port_name);
		vid.node_name = wwn_to_u64(entry->node_name);

		ql_dbg(ql_dbg_user, vha, 0x7093,
		    "NPIV[%02x]: wwpn=%llx "
		    "wwnn=%llx vf_id=0x%x Q_qos=0x%x F_qos=0x%x.\n", cnt,
		    (unsigned long long)vid.port_name,
		    (unsigned long long)vid.node_name,
		    le16_to_cpu(entry->vf_id),
		    entry->q_qos, entry->f_qos);

		if (i < QLA_PRECONFIG_VPORTS) {
			vport = fc_vport_create(vha->host, 0, &vid);
			if (!vport)
				ql_log(ql_log_warn, vha, 0x7094,
				    "NPIV-Config Failed to create vport [%02x]: "
				    "wwpn=%llx wwnn=%llx.\n", cnt,
				    (unsigned long long)vid.port_name,
				    (unsigned long long)vid.node_name);
		}
	}
done:
	kfree(data);
}