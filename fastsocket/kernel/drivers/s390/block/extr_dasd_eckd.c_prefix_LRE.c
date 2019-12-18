#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  unsigned int u16 ;
struct TYPE_12__ {scalar_t__ operation; int nr_cyl; } ;
struct TYPE_13__ {int cu_type; unsigned int trk_per_cyl; } ;
struct TYPE_9__ {scalar_t__ type; } ;
struct dasd_eckd_private {int real_cyl; TYPE_5__ attrib; TYPE_6__ rdc_data; scalar_t__ uses_cdl; TYPE_2__ uid; TYPE_1__* ned; } ;
struct dasd_device {scalar_t__ private; } ;
struct ccw1 {int count; void* cda; scalar_t__ flags; int /*<<< orphan*/  cmd_code; } ;
struct TYPE_10__ {int define_extent; int verify_base; int hyper_pav; } ;
struct LRE_eckd_data {int dummy; } ;
struct TYPE_14__ {scalar_t__ operation; int mode; } ;
struct TYPE_11__ {int perm; int auth; } ;
struct DE_eckd_data {unsigned int blk_size; int ga_extended; int /*<<< orphan*/  end_ext; int /*<<< orphan*/  beg_ext; TYPE_7__ attributes; TYPE_4__ mask; } ;
struct PFX_eckd_data {unsigned char format; TYPE_3__ validity; int /*<<< orphan*/  base_lss; int /*<<< orphan*/  base_address; struct LRE_eckd_data locate_record; struct DE_eckd_data define_extent; } ;
typedef  void* __u32 ;
struct TYPE_8__ {int /*<<< orphan*/  ID; int /*<<< orphan*/  unit_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 void* DASD_BYPASS_CACHE ; 
#define  DASD_ECKD_CCW_ERASE 149 
 int /*<<< orphan*/  DASD_ECKD_CCW_PFX ; 
#define  DASD_ECKD_CCW_READ 148 
#define  DASD_ECKD_CCW_READ_CKD 147 
#define  DASD_ECKD_CCW_READ_CKD_MT 146 
#define  DASD_ECKD_CCW_READ_COUNT 145 
#define  DASD_ECKD_CCW_READ_HOME_ADDRESS 144 
#define  DASD_ECKD_CCW_READ_KD 143 
#define  DASD_ECKD_CCW_READ_KD_MT 142 
#define  DASD_ECKD_CCW_READ_MT 141 
#define  DASD_ECKD_CCW_READ_RECORD_ZERO 140 
#define  DASD_ECKD_CCW_READ_TRACK 139 
#define  DASD_ECKD_CCW_READ_TRACK_DATA 138 
#define  DASD_ECKD_CCW_WRITE 137 
#define  DASD_ECKD_CCW_WRITE_CKD 136 
#define  DASD_ECKD_CCW_WRITE_CKD_MT 135 
#define  DASD_ECKD_CCW_WRITE_FULL_TRACK 134 
#define  DASD_ECKD_CCW_WRITE_HOME_ADDRESS 133 
#define  DASD_ECKD_CCW_WRITE_KD 132 
#define  DASD_ECKD_CCW_WRITE_KD_MT 131 
#define  DASD_ECKD_CCW_WRITE_MT 130 
#define  DASD_ECKD_CCW_WRITE_RECORD_ZERO 129 
#define  DASD_ECKD_CCW_WRITE_TRACK_DATA 128 
 scalar_t__ DASD_SEQ_ACCESS ; 
 scalar_t__ DASD_SEQ_PRESTAGE ; 
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,int) ; 
 int /*<<< orphan*/  DBF_ERR ; 
 int EINVAL ; 
 scalar_t__ UA_BASE_DEVICE ; 
 scalar_t__ UA_HYPER_PAV_ALIAS ; 
 scalar_t__ __pa (struct PFX_eckd_data*) ; 
 int check_XRC_on_prefix (struct PFX_eckd_data*,struct dasd_device*) ; 
 int /*<<< orphan*/  fill_LRE_data (struct LRE_eckd_data*,unsigned int,unsigned int,int,int,struct dasd_device*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  memset (struct PFX_eckd_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_ch_t (int /*<<< orphan*/ *,int,unsigned int) ; 

__attribute__((used)) static int prefix_LRE(struct ccw1 *ccw, struct PFX_eckd_data *pfxdata,
		      unsigned int trk, unsigned int totrk, int cmd,
		      struct dasd_device *basedev, struct dasd_device *startdev,
		      unsigned char format, unsigned int rec_on_trk, int count,
		      unsigned int blksize, unsigned int tlf)
{
	struct dasd_eckd_private *basepriv, *startpriv;
	struct DE_eckd_data *dedata;
	struct LRE_eckd_data *lredata;
	u32 begcyl, endcyl;
	u16 heads, beghead, endhead;
	int rc = 0;

	basepriv = (struct dasd_eckd_private *) basedev->private;
	startpriv = (struct dasd_eckd_private *) startdev->private;
	dedata = &pfxdata->define_extent;
	lredata = &pfxdata->locate_record;

	ccw->cmd_code = DASD_ECKD_CCW_PFX;
	ccw->flags = 0;
	if (cmd == DASD_ECKD_CCW_WRITE_FULL_TRACK) {
		ccw->count = sizeof(*pfxdata) + 2;
		ccw->cda = (__u32) __pa(pfxdata);
		memset(pfxdata, 0, sizeof(*pfxdata) + 2);
	} else {
		ccw->count = sizeof(*pfxdata);
		ccw->cda = (__u32) __pa(pfxdata);
		memset(pfxdata, 0, sizeof(*pfxdata));
	}

	/* prefix data */
	if (format > 1) {
		DBF_DEV_EVENT(DBF_ERR, basedev,
			      "PFX LRE unknown format 0x%x", format);
		BUG();
		return -EINVAL;
	}
	pfxdata->format = format;
	pfxdata->base_address = basepriv->ned->unit_addr;
	pfxdata->base_lss = basepriv->ned->ID;
	pfxdata->validity.define_extent = 1;

	/* private uid is kept up to date, conf_data may be outdated */
	if (startpriv->uid.type != UA_BASE_DEVICE) {
		pfxdata->validity.verify_base = 1;
		if (startpriv->uid.type == UA_HYPER_PAV_ALIAS)
			pfxdata->validity.hyper_pav = 1;
	}

	/* define extend data (mostly)*/
	switch (cmd) {
	case DASD_ECKD_CCW_READ_HOME_ADDRESS:
	case DASD_ECKD_CCW_READ_RECORD_ZERO:
	case DASD_ECKD_CCW_READ:
	case DASD_ECKD_CCW_READ_MT:
	case DASD_ECKD_CCW_READ_CKD:
	case DASD_ECKD_CCW_READ_CKD_MT:
	case DASD_ECKD_CCW_READ_KD:
	case DASD_ECKD_CCW_READ_KD_MT:
	case DASD_ECKD_CCW_READ_COUNT:
		dedata->mask.perm = 0x1;
		dedata->attributes.operation = basepriv->attrib.operation;
		break;
	case DASD_ECKD_CCW_READ_TRACK:
	case DASD_ECKD_CCW_READ_TRACK_DATA:
		dedata->mask.perm = 0x1;
		dedata->attributes.operation = basepriv->attrib.operation;
		dedata->blk_size = 0;
		break;
	case DASD_ECKD_CCW_WRITE:
	case DASD_ECKD_CCW_WRITE_MT:
	case DASD_ECKD_CCW_WRITE_KD:
	case DASD_ECKD_CCW_WRITE_KD_MT:
		dedata->mask.perm = 0x02;
		dedata->attributes.operation = basepriv->attrib.operation;
		rc = check_XRC_on_prefix(pfxdata, basedev);
		break;
	case DASD_ECKD_CCW_WRITE_CKD:
	case DASD_ECKD_CCW_WRITE_CKD_MT:
		dedata->attributes.operation = DASD_BYPASS_CACHE;
		rc = check_XRC_on_prefix(pfxdata, basedev);
		break;
	case DASD_ECKD_CCW_ERASE:
	case DASD_ECKD_CCW_WRITE_HOME_ADDRESS:
	case DASD_ECKD_CCW_WRITE_RECORD_ZERO:
		dedata->mask.perm = 0x3;
		dedata->mask.auth = 0x1;
		dedata->attributes.operation = DASD_BYPASS_CACHE;
		rc = check_XRC_on_prefix(pfxdata, basedev);
		break;
	case DASD_ECKD_CCW_WRITE_FULL_TRACK:
		dedata->mask.perm = 0x03;
		dedata->attributes.operation = basepriv->attrib.operation;
		dedata->blk_size = 0;
		break;
	case DASD_ECKD_CCW_WRITE_TRACK_DATA:
		dedata->mask.perm = 0x02;
		dedata->attributes.operation = basepriv->attrib.operation;
		dedata->blk_size = blksize;
		rc = check_XRC_on_prefix(pfxdata, basedev);
		break;
	default:
		DBF_DEV_EVENT(DBF_ERR, basedev,
			    "PFX LRE unknown opcode 0x%x", cmd);
		BUG();
		return -EINVAL;
	}

	dedata->attributes.mode = 0x3;	/* ECKD */

	if ((basepriv->rdc_data.cu_type == 0x2105 ||
	     basepriv->rdc_data.cu_type == 0x2107 ||
	     basepriv->rdc_data.cu_type == 0x1750)
	    && !(basepriv->uses_cdl && trk < 2))
		dedata->ga_extended |= 0x40; /* Regular Data Format Mode */

	heads = basepriv->rdc_data.trk_per_cyl;
	begcyl = trk / heads;
	beghead = trk % heads;
	endcyl = totrk / heads;
	endhead = totrk % heads;

	/* check for sequential prestage - enhance cylinder range */
	if (dedata->attributes.operation == DASD_SEQ_PRESTAGE ||
	    dedata->attributes.operation == DASD_SEQ_ACCESS) {

		if (endcyl + basepriv->attrib.nr_cyl < basepriv->real_cyl)
			endcyl += basepriv->attrib.nr_cyl;
		else
			endcyl = (basepriv->real_cyl - 1);
	}

	set_ch_t(&dedata->beg_ext, begcyl, beghead);
	set_ch_t(&dedata->end_ext, endcyl, endhead);

	if (format == 1) {
		fill_LRE_data(lredata, trk, rec_on_trk, count, cmd,
			      basedev, blksize, tlf);
	}

	return rc;
}