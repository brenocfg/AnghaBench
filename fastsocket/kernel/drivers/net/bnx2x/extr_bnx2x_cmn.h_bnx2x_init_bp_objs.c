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
struct bnx2x {int /*<<< orphan*/  sp_state; TYPE_1__* fp; int /*<<< orphan*/  rss_conf_obj; int /*<<< orphan*/  vlans_pool; int /*<<< orphan*/  macs_pool; int /*<<< orphan*/  mcast_obj; int /*<<< orphan*/  rx_mode_obj; } ;
struct TYPE_2__ {int /*<<< orphan*/  cid; int /*<<< orphan*/  cl_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_FILTER_MCAST_PENDING ; 
 int /*<<< orphan*/  BNX2X_FILTER_RSS_CONF_PENDING ; 
 int /*<<< orphan*/  BNX2X_OBJ_TYPE_RX ; 
 int BP_ABS_FUNC (struct bnx2x*) ; 
 int /*<<< orphan*/  BP_FUNC (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_get_path_func_num (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_init_mac_credit_pool (struct bnx2x*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_init_mcast_obj (struct bnx2x*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_init_rss_config_obj (struct bnx2x*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_init_rx_mode_obj (struct bnx2x*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2x_init_vlan_credit_pool (struct bnx2x*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_sp (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_sp_mapping (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcast_rdata ; 
 int /*<<< orphan*/  rss_rdata ; 

__attribute__((used)) static inline void bnx2x_init_bp_objs(struct bnx2x *bp)
{
	/* RX_MODE controlling object */
	bnx2x_init_rx_mode_obj(bp, &bp->rx_mode_obj);

	/* multicast configuration controlling object */
	bnx2x_init_mcast_obj(bp, &bp->mcast_obj, bp->fp->cl_id, bp->fp->cid,
			     BP_FUNC(bp), BP_FUNC(bp),
			     bnx2x_sp(bp, mcast_rdata),
			     bnx2x_sp_mapping(bp, mcast_rdata),
			     BNX2X_FILTER_MCAST_PENDING, &bp->sp_state,
			     BNX2X_OBJ_TYPE_RX);

	/* Setup CAM credit pools */
	bnx2x_init_mac_credit_pool(bp, &bp->macs_pool, BP_FUNC(bp),
				   bnx2x_get_path_func_num(bp));

	bnx2x_init_vlan_credit_pool(bp, &bp->vlans_pool, BP_ABS_FUNC(bp)>>1,
				    bnx2x_get_path_func_num(bp));

	/* RSS configuration object */
	bnx2x_init_rss_config_obj(bp, &bp->rss_conf_obj, bp->fp->cl_id,
				  bp->fp->cid, BP_FUNC(bp), BP_FUNC(bp),
				  bnx2x_sp(bp, rss_rdata),
				  bnx2x_sp_mapping(bp, rss_rdata),
				  BNX2X_FILTER_RSS_CONF_PENDING, &bp->sp_state,
				  BNX2X_OBJ_TYPE_RX);
}