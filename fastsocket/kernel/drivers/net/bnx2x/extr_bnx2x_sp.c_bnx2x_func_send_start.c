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
typedef  scalar_t__ u8 ;
struct function_start_data {int /*<<< orphan*/  gre_tunnel_rss; int /*<<< orphan*/  gre_tunnel_mode; int /*<<< orphan*/  network_cos_mode; int /*<<< orphan*/  path_id; int /*<<< orphan*/  sd_vlan_tag; scalar_t__ function_mode; } ;
struct bnx2x_func_start_params {int /*<<< orphan*/  gre_tunnel_rss; int /*<<< orphan*/  gre_tunnel_mode; int /*<<< orphan*/  network_cos_mode; int /*<<< orphan*/  sd_vlan_tag; scalar_t__ mf_mode; } ;
struct TYPE_2__ {struct bnx2x_func_start_params start; } ;
struct bnx2x_func_state_params {TYPE_1__ params; struct bnx2x_func_sp_obj* f_obj; } ;
struct bnx2x_func_sp_obj {int /*<<< orphan*/  rdata_mapping; scalar_t__ rdata; } ;
struct bnx2x {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BP_PATH (struct bnx2x*) ; 
 int /*<<< orphan*/  NONE_CONNECTION_TYPE ; 
 int /*<<< orphan*/  RAMROD_CMD_ID_COMMON_FUNCTION_START ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 int bnx2x_sp_post (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct function_start_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int bnx2x_func_send_start(struct bnx2x *bp,
					struct bnx2x_func_state_params *params)
{
	struct bnx2x_func_sp_obj *o = params->f_obj;
	struct function_start_data *rdata =
		(struct function_start_data *)o->rdata;
	dma_addr_t data_mapping = o->rdata_mapping;
	struct bnx2x_func_start_params *start_params = &params->params.start;

	memset(rdata, 0, sizeof(*rdata));

	/* Fill the ramrod data with provided parameters */
	rdata->function_mode	= (u8)start_params->mf_mode;
	rdata->sd_vlan_tag	= cpu_to_le16(start_params->sd_vlan_tag);
	rdata->path_id		= BP_PATH(bp);
	rdata->network_cos_mode	= start_params->network_cos_mode;
	rdata->gre_tunnel_mode	= start_params->gre_tunnel_mode;
	rdata->gre_tunnel_rss	= start_params->gre_tunnel_rss;

	/* No need for an explicit memory barrier here as long we would
	 * need to ensure the ordering of writing to the SPQ element
	 * and updating of the SPQ producer which involves a memory
	 * read and we will have to put a full memory barrier there
	 * (inside bnx2x_sp_post()).
	 */

	return bnx2x_sp_post(bp, RAMROD_CMD_ID_COMMON_FUNCTION_START, 0,
			     U64_HI(data_mapping),
			     U64_LO(data_mapping), NONE_CONNECTION_TYPE);
}