#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct qla_hw_data {int link_data_rate; int /*<<< orphan*/  ms_iocb_dma; int /*<<< orphan*/  ms_iocb; TYPE_1__* init_cb; TYPE_4__* ct_sns; TYPE_2__* isp_ops; } ;
struct init_cb_24xx {int /*<<< orphan*/  frame_payload_size; } ;
struct ct_sns_rsp {int dummy; } ;
struct TYPE_21__ {void* count; } ;
struct TYPE_22__ {int /*<<< orphan*/ * port_name; TYPE_5__ attrs; } ;
struct TYPE_23__ {TYPE_6__ rpa; } ;
struct ct_sns_req {TYPE_7__ req; } ;
struct TYPE_24__ {int* fc4_types; char* os_dev_name; char* host_name; int /*<<< orphan*/  max_frame_size; void* cur_speed; void* sup_speed; } ;
struct ct_fdmi_port_attr {TYPE_8__ a; void* len; void* type; } ;
struct TYPE_25__ {int /*<<< orphan*/  host; int /*<<< orphan*/  port_name; struct qla_hw_data* hw; } ;
typedef  TYPE_9__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  ms_iocb_entry_t ;
struct TYPE_19__ {struct ct_sns_rsp rsp; int /*<<< orphan*/  req; } ;
struct TYPE_20__ {TYPE_3__ p; } ;
struct TYPE_18__ {int /*<<< orphan*/ * (* prep_ms_fdmi_iocb ) (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_17__ {int /*<<< orphan*/  frame_payload_size; } ;

/* Variables and functions */
 int FDMI_PORT_ATTR_COUNT ; 
 int FDMI_PORT_CURRENT_SPEED ; 
 int FDMI_PORT_FC4_TYPES ; 
 int FDMI_PORT_HOST_NAME ; 
 int FDMI_PORT_MAX_FRAME_SIZE ; 
 int FDMI_PORT_OS_DEVICE_NAME ; 
 int FDMI_PORT_SPEED_10GB ; 
 int FDMI_PORT_SPEED_16GB ; 
 int FDMI_PORT_SPEED_1GB ; 
 int FDMI_PORT_SPEED_2GB ; 
 int FDMI_PORT_SPEED_4GB ; 
 int FDMI_PORT_SPEED_8GB ; 
 int FDMI_PORT_SPEED_UNKNOWN ; 
 int FDMI_PORT_SUPPORT_SPEED ; 
 scalar_t__ IS_CNA_CAPABLE (struct qla_hw_data*) ; 
 scalar_t__ IS_FWI2_CAPABLE (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA23XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA24XX_TYPE (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA25XX (struct qla_hw_data*) ; 
#define  PORT_SPEED_10GB 133 
#define  PORT_SPEED_16GB 132 
#define  PORT_SPEED_1GB 131 
#define  PORT_SPEED_2GB 130 
#define  PORT_SPEED_4GB 129 
#define  PORT_SPEED_8GB 128 
 int /*<<< orphan*/  QLA2XXX_DRIVER_NAME ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  RPA_CMD ; 
 int /*<<< orphan*/  RPA_RSP_SIZE ; 
 int WWN_SIZE ; 
 void* __constant_cpu_to_be16 (int) ; 
 void* __constant_cpu_to_be32 (int) ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 char* fc_host_system_hostname (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_dbg (scalar_t__,TYPE_9__*,int,char*,...) ; 
 scalar_t__ ql_dbg_buffer ; 
 scalar_t__ ql_dbg_disc ; 
 int /*<<< orphan*/  ql_dump_buffer (scalar_t__,TYPE_9__*,int,int /*<<< orphan*/ *,int) ; 
 int qla2x00_chk_ms_status (TYPE_9__*,int /*<<< orphan*/ *,struct ct_sns_rsp*,char*) ; 
 int qla2x00_issue_iocb (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ct_sns_req* qla2x00_prep_ct_fdmi_req (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_update_ms_fdmi_iocb (TYPE_9__*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/ * stub1 (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qla2x00_fdmi_rpa(scsi_qla_host_t *vha)
{
	int rval, alen;
	uint32_t size, max_frame_size;
	struct qla_hw_data *ha = vha->hw;
	ms_iocb_entry_t *ms_pkt;
	struct ct_sns_req *ct_req;
	struct ct_sns_rsp *ct_rsp;
	uint8_t *entries;
	struct ct_fdmi_port_attr *eiter;
	struct init_cb_24xx *icb24 = (struct init_cb_24xx *)ha->init_cb;

	/* Issue RPA */
	/* Prepare common MS IOCB */
	/*   Request size adjusted after CT preparation */
	ms_pkt = ha->isp_ops->prep_ms_fdmi_iocb(vha, 0, RPA_RSP_SIZE);

	/* Prepare CT request */
	ct_req = qla2x00_prep_ct_fdmi_req(&ha->ct_sns->p.req, RPA_CMD,
	    RPA_RSP_SIZE);
	ct_rsp = &ha->ct_sns->p.rsp;

	/* Prepare FDMI command arguments -- attribute block, attributes. */
	memcpy(ct_req->req.rpa.port_name, vha->port_name, WWN_SIZE);
	size = WWN_SIZE + 4;

	/* Attributes */
	ct_req->req.rpa.attrs.count =
	    __constant_cpu_to_be32(FDMI_PORT_ATTR_COUNT - 1);
	entries = ct_req->req.rpa.port_name;

	/* FC4 types. */
	eiter = (struct ct_fdmi_port_attr *) (entries + size);
	eiter->type = __constant_cpu_to_be16(FDMI_PORT_FC4_TYPES);
	eiter->len = __constant_cpu_to_be16(4 + 32);
	eiter->a.fc4_types[2] = 0x01;
	size += 4 + 32;

	ql_dbg(ql_dbg_disc, vha, 0x2039,
	    "FC4_TYPES=%02x %02x.\n",
	    eiter->a.fc4_types[2],
	    eiter->a.fc4_types[1]);

	/* Supported speed. */
	eiter = (struct ct_fdmi_port_attr *) (entries + size);
	eiter->type = __constant_cpu_to_be16(FDMI_PORT_SUPPORT_SPEED);
	eiter->len = __constant_cpu_to_be16(4 + 4);
	if (IS_CNA_CAPABLE(ha))
		eiter->a.sup_speed = __constant_cpu_to_be32(
		    FDMI_PORT_SPEED_10GB);
	else if (IS_QLA25XX(ha))
		eiter->a.sup_speed = __constant_cpu_to_be32(
		    FDMI_PORT_SPEED_1GB|FDMI_PORT_SPEED_2GB|
		    FDMI_PORT_SPEED_4GB|FDMI_PORT_SPEED_8GB);
	else if (IS_QLA24XX_TYPE(ha))
		eiter->a.sup_speed = __constant_cpu_to_be32(
		    FDMI_PORT_SPEED_1GB|FDMI_PORT_SPEED_2GB|
		    FDMI_PORT_SPEED_4GB);
	else if (IS_QLA23XX(ha))
		eiter->a.sup_speed =__constant_cpu_to_be32(
		    FDMI_PORT_SPEED_1GB|FDMI_PORT_SPEED_2GB);
	else
		eiter->a.sup_speed = __constant_cpu_to_be32(
		    FDMI_PORT_SPEED_1GB);
	size += 4 + 4;

	ql_dbg(ql_dbg_disc, vha, 0x203a,
	    "Supported_Speed=%x.\n", eiter->a.sup_speed);

	/* Current speed. */
	eiter = (struct ct_fdmi_port_attr *) (entries + size);
	eiter->type = __constant_cpu_to_be16(FDMI_PORT_CURRENT_SPEED);
	eiter->len = __constant_cpu_to_be16(4 + 4);
	switch (ha->link_data_rate) {
	case PORT_SPEED_1GB:
		eiter->a.cur_speed =
		    __constant_cpu_to_be32(FDMI_PORT_SPEED_1GB);
		break;
	case PORT_SPEED_2GB:
		eiter->a.cur_speed =
		    __constant_cpu_to_be32(FDMI_PORT_SPEED_2GB);
		break;
	case PORT_SPEED_4GB:
		eiter->a.cur_speed =
		    __constant_cpu_to_be32(FDMI_PORT_SPEED_4GB);
		break;
	case PORT_SPEED_8GB:
		eiter->a.cur_speed =
		    __constant_cpu_to_be32(FDMI_PORT_SPEED_8GB);
		break;
	case PORT_SPEED_10GB:
		eiter->a.cur_speed =
		    __constant_cpu_to_be32(FDMI_PORT_SPEED_10GB);
		break;
	case PORT_SPEED_16GB:
		eiter->a.cur_speed =
		    __constant_cpu_to_be32(FDMI_PORT_SPEED_16GB);
		break;
	default:
		eiter->a.cur_speed =
		    __constant_cpu_to_be32(FDMI_PORT_SPEED_UNKNOWN);
		break;
	}
	size += 4 + 4;

	ql_dbg(ql_dbg_disc, vha, 0x203b,
	    "Current_Speed=%x.\n", eiter->a.cur_speed);

	/* Max frame size. */
	eiter = (struct ct_fdmi_port_attr *) (entries + size);
	eiter->type = __constant_cpu_to_be16(FDMI_PORT_MAX_FRAME_SIZE);
	eiter->len = __constant_cpu_to_be16(4 + 4);
	max_frame_size = IS_FWI2_CAPABLE(ha) ?
	    le16_to_cpu(icb24->frame_payload_size):
	    le16_to_cpu(ha->init_cb->frame_payload_size);
	eiter->a.max_frame_size = cpu_to_be32(max_frame_size);
	size += 4 + 4;

	ql_dbg(ql_dbg_disc, vha, 0x203c,
	    "Max_Frame_Size=%x.\n", eiter->a.max_frame_size);

	/* OS device name. */
	eiter = (struct ct_fdmi_port_attr *) (entries + size);
	eiter->type = __constant_cpu_to_be16(FDMI_PORT_OS_DEVICE_NAME);
	strcpy(eiter->a.os_dev_name, QLA2XXX_DRIVER_NAME);
	alen = strlen(eiter->a.os_dev_name);
	alen += (alen & 3) ? (4 - (alen & 3)) : 4;
	eiter->len = cpu_to_be16(4 + alen);
	size += 4 + alen;

	ql_dbg(ql_dbg_disc, vha, 0x204b,
	    "OS_Device_Name=%s.\n", eiter->a.os_dev_name);

	/* Hostname. */
	if (strlen(fc_host_system_hostname(vha->host))) {
		ct_req->req.rpa.attrs.count =
		    __constant_cpu_to_be32(FDMI_PORT_ATTR_COUNT);
		eiter = (struct ct_fdmi_port_attr *) (entries + size);
		eiter->type = __constant_cpu_to_be16(FDMI_PORT_HOST_NAME);
		snprintf(eiter->a.host_name, sizeof(eiter->a.host_name),
		    "%s", fc_host_system_hostname(vha->host));
		alen = strlen(eiter->a.host_name);
		alen += (alen & 3) ? (4 - (alen & 3)) : 4;
		eiter->len = cpu_to_be16(4 + alen);
		size += 4 + alen;

		ql_dbg(ql_dbg_disc, vha, 0x203d,
		    "HostName=%s.\n", eiter->a.host_name);
	}

	/* Update MS request size. */
	qla2x00_update_ms_fdmi_iocb(vha, size + 16);

	ql_dbg(ql_dbg_disc, vha, 0x203e,
	    "RPA portname= %02x%02x%02x%02x%02X%02x%02x%02x size=%d.\n",
	    ct_req->req.rpa.port_name[0], ct_req->req.rpa.port_name[1],
	    ct_req->req.rpa.port_name[2], ct_req->req.rpa.port_name[3],
	    ct_req->req.rpa.port_name[4], ct_req->req.rpa.port_name[5],
	    ct_req->req.rpa.port_name[6], ct_req->req.rpa.port_name[7],
	    size);
	ql_dump_buffer(ql_dbg_disc + ql_dbg_buffer, vha, 0x2079,
	    entries, size);

	/* Execute MS IOCB */
	rval = qla2x00_issue_iocb(vha, ha->ms_iocb, ha->ms_iocb_dma,
	    sizeof(ms_iocb_entry_t));
	if (rval != QLA_SUCCESS) {
		/*EMPTY*/
		ql_dbg(ql_dbg_disc, vha, 0x2040,
		    "RPA issue IOCB failed (%d).\n", rval);
	} else if (qla2x00_chk_ms_status(vha, ms_pkt, ct_rsp, "RPA") !=
	    QLA_SUCCESS) {
		rval = QLA_FUNCTION_FAILED;
	} else {
		ql_dbg(ql_dbg_disc, vha, 0x2041,
		    "RPA exiting nornally.\n");
	}

	return rval;
}