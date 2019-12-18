#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {char* opcode; } ;
struct TYPE_18__ {TYPE_8__ rsp; } ;
struct TYPE_16__ {int status; } ;
struct viosrp_host_config {TYPE_7__ common; } ;
struct TYPE_14__ {int /*<<< orphan*/  length; int /*<<< orphan*/  status; } ;
struct viosrp_adapter_info {TYPE_5__ common; int /*<<< orphan*/  buffer; } ;
struct TYPE_12__ {int status; } ;
struct TYPE_13__ {TYPE_3__ common; } ;
struct TYPE_10__ {int type; } ;
struct TYPE_11__ {TYPE_1__ common; } ;
struct TYPE_15__ {struct viosrp_host_config host_config; struct viosrp_adapter_info adapter_info; TYPE_4__ error_log; TYPE_2__ empty_iu; } ;
union viosrp_iu {TYPE_9__ srp; TYPE_6__ mad; } ;
struct iu_entry {int dummy; } ;

/* Variables and functions */
#define  VIOSRP_ADAPTER_INFO_TYPE 131 
#define  VIOSRP_EMPTY_IU_TYPE 130 
#define  VIOSRP_ERROR_LOG_TYPE 129 
#define  VIOSRP_HOST_CONFIG_TYPE 128 
 int /*<<< orphan*/  VIOSRP_MAD_FORMAT ; 
 int /*<<< orphan*/  eprintk (char*,char*) ; 
 int /*<<< orphan*/  send_adapter_info (struct iu_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_iu (struct iu_entry*,int,int /*<<< orphan*/ ) ; 
 union viosrp_iu* vio_iu (struct iu_entry*) ; 

__attribute__((used)) static int process_mad_iu(struct iu_entry *iue)
{
	union viosrp_iu *iu = vio_iu(iue);
	struct viosrp_adapter_info *info;
	struct viosrp_host_config *conf;

	switch (iu->mad.empty_iu.common.type) {
	case VIOSRP_EMPTY_IU_TYPE:
		eprintk("%s\n", "Unsupported EMPTY MAD IU");
		break;
	case VIOSRP_ERROR_LOG_TYPE:
		eprintk("%s\n", "Unsupported ERROR LOG MAD IU");
		iu->mad.error_log.common.status = 1;
		send_iu(iue, sizeof(iu->mad.error_log),	VIOSRP_MAD_FORMAT);
		break;
	case VIOSRP_ADAPTER_INFO_TYPE:
		info = &iu->mad.adapter_info;
		info->common.status = send_adapter_info(iue, info->buffer,
							info->common.length);
		send_iu(iue, sizeof(*info), VIOSRP_MAD_FORMAT);
		break;
	case VIOSRP_HOST_CONFIG_TYPE:
		conf = &iu->mad.host_config;
		conf->common.status = 1;
		send_iu(iue, sizeof(*conf), VIOSRP_MAD_FORMAT);
		break;
	default:
		eprintk("Unknown type %u\n", iu->srp.rsp.opcode);
	}

	return 1;
}