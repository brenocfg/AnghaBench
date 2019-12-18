#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct fchs_s {int dummy; } ;
struct fc_rnid_general_topology_data_s {int dummy; } ;
struct fc_rnid_common_id_data_s {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  els_code; } ;
struct fc_rnid_acc_s {int common_id_data_length; int specific_id_data_length; struct fc_rnid_general_topology_data_s gen_topology_data; struct fc_rnid_common_id_data_s common_id_data; scalar_t__ node_id_data_format; TYPE_1__ els_cmd; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  FC_ELS_ACC ; 
 scalar_t__ RNID_NODEID_DATA_FORMAT_DISCOVERY ; 
 int /*<<< orphan*/  fc_els_rsp_build (struct fchs_s*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fc_rnid_acc_s*,int /*<<< orphan*/ ,int) ; 

u16
fc_rnid_acc_build(struct fchs_s *fchs, struct fc_rnid_acc_s *rnid_acc, u32 d_id,
		  u32 s_id, __be16 ox_id, u32 data_format,
		  struct fc_rnid_common_id_data_s *common_id_data,
		  struct fc_rnid_general_topology_data_s *gen_topo_data)
{
	memset(rnid_acc, 0, sizeof(struct fc_rnid_acc_s));

	fc_els_rsp_build(fchs, d_id, s_id, ox_id);

	rnid_acc->els_cmd.els_code = FC_ELS_ACC;
	rnid_acc->node_id_data_format = data_format;
	rnid_acc->common_id_data_length =
			sizeof(struct fc_rnid_common_id_data_s);
	rnid_acc->common_id_data = *common_id_data;

	if (data_format == RNID_NODEID_DATA_FORMAT_DISCOVERY) {
		rnid_acc->specific_id_data_length =
			sizeof(struct fc_rnid_general_topology_data_s);
		rnid_acc->gen_topology_data = *gen_topo_data;
		return sizeof(struct fc_rnid_acc_s);
	} else {
		return sizeof(struct fc_rnid_acc_s) -
			sizeof(struct fc_rnid_general_topology_data_s);
	}

}