#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  app_start_hdl; int /*<<< orphan*/  gap_start_hdl; int /*<<< orphan*/  gatt_start_hdl; } ;
struct TYPE_8__ {int max_transmit; int rtrans_tout; int mon_tout; int mps; int tx_win_sz; int /*<<< orphan*/  mode; } ;
struct TYPE_10__ {int default_idle_tout; TYPE_2__ hdl_cfg; int /*<<< orphan*/  pL2CA_FixedCong_Cb; int /*<<< orphan*/  pL2CA_FixedData_Cb; int /*<<< orphan*/  pL2CA_FixedConn_Cb; TYPE_1__ fixed_chnl_opts; void* pending_new_srv_start_q; void* srv_chg_clt_q; void* sign_op_queue; int /*<<< orphan*/  def_mtu_size; int /*<<< orphan*/  trace_level; } ;
typedef  TYPE_3__ tL2CAP_FIXED_CHNL_REG ;
typedef  int /*<<< orphan*/  tL2CAP_APPL_INFO ;
typedef  int /*<<< orphan*/  tGATT_CB ;
struct TYPE_11__ {int /*<<< orphan*/  local_mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_SEC_NONE ; 
 int /*<<< orphan*/  BTM_SEC_SERVICE_ATT ; 
 int /*<<< orphan*/  BTM_SetSecurityLevel (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_PSM_ATT ; 
 int /*<<< orphan*/  BT_TRACE_LEVEL_NONE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GATT_APP_START_HANDLE ; 
 int /*<<< orphan*/  GATT_DEF_BLE_MTU_SIZE ; 
 int /*<<< orphan*/  GATT_GAP_START_HANDLE ; 
 int /*<<< orphan*/  GATT_GATT_START_HANDLE ; 
 int /*<<< orphan*/  GATT_INITIAL_TRACE_LEVEL ; 
 int /*<<< orphan*/  GATT_MAX_MTU_SIZE ; 
 int /*<<< orphan*/  GATT_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  L2CAP_ATT_CID ; 
 int /*<<< orphan*/  L2CAP_FCR_BASIC_MODE ; 
 int /*<<< orphan*/  L2CA_Register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  L2CA_RegisterFixedChannel (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  QUEUE_SIZE_MAX ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dyn_info ; 
 void* fixed_queue_new (int /*<<< orphan*/ ) ; 
 TYPE_3__ gatt_cb ; 
 int /*<<< orphan*/ * gatt_cb_ptr ; 
 TYPE_5__ gatt_default ; 
 int /*<<< orphan*/  gatt_le_cong_cback ; 
 int /*<<< orphan*/  gatt_le_connect_cback ; 
 int /*<<< orphan*/  gatt_le_data_ind ; 
 int /*<<< orphan*/  gatt_profile_db_init () ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osi_malloc (int) ; 

void gatt_init (void)
{
    tL2CAP_FIXED_CHNL_REG  fixed_reg;
#if GATT_DYNAMIC_MEMORY
    gatt_cb_ptr = (tGATT_CB *)osi_malloc(sizeof(tGATT_CB));
#endif /* #if GATT_DYNAMIC_MEMORY */
    memset (&gatt_cb, 0, sizeof(tGATT_CB));
    memset (&fixed_reg, 0, sizeof(tL2CAP_FIXED_CHNL_REG));

#if defined(GATT_INITIAL_TRACE_LEVEL)
    gatt_cb.trace_level = GATT_INITIAL_TRACE_LEVEL;
#else
    gatt_cb.trace_level = BT_TRACE_LEVEL_NONE;    /* No traces */
#endif
    gatt_cb.def_mtu_size = GATT_DEF_BLE_MTU_SIZE;
    gatt_cb.sign_op_queue = fixed_queue_new(QUEUE_SIZE_MAX);
    gatt_cb.srv_chg_clt_q = fixed_queue_new(QUEUE_SIZE_MAX);
    gatt_cb.pending_new_srv_start_q = fixed_queue_new(QUEUE_SIZE_MAX);
    /* First, register fixed L2CAP channel for ATT over BLE */
    fixed_reg.fixed_chnl_opts.mode         = L2CAP_FCR_BASIC_MODE;
    fixed_reg.fixed_chnl_opts.max_transmit = 0xFF;
    fixed_reg.fixed_chnl_opts.rtrans_tout  = 2000;
    fixed_reg.fixed_chnl_opts.mon_tout     = 12000;
    fixed_reg.fixed_chnl_opts.mps          = 670;
    fixed_reg.fixed_chnl_opts.tx_win_sz    = 1;

    fixed_reg.pL2CA_FixedConn_Cb = gatt_le_connect_cback;
    fixed_reg.pL2CA_FixedData_Cb = gatt_le_data_ind;
    fixed_reg.pL2CA_FixedCong_Cb = gatt_le_cong_cback;      /* congestion callback */
    fixed_reg.default_idle_tout  = 0xffff;                  /* 0xffff default idle timeout */

    L2CA_RegisterFixedChannel (L2CAP_ATT_CID, &fixed_reg);

#if (CLASSIC_BT_GATT_INCLUDED == TRUE)
    /* Now, register with L2CAP for ATT PSM over BR/EDR */
    if (!L2CA_Register (BT_PSM_ATT, (tL2CAP_APPL_INFO *) &dyn_info)) {
        GATT_TRACE_ERROR ("ATT Dynamic Registration failed");
    }
#endif  ///CLASSIC_BT_GATT_INCLUDED == TRUE
    BTM_SetSecurityLevel(TRUE, "", BTM_SEC_SERVICE_ATT, BTM_SEC_NONE, BT_PSM_ATT, 0, 0);
    BTM_SetSecurityLevel(FALSE, "", BTM_SEC_SERVICE_ATT, BTM_SEC_NONE, BT_PSM_ATT, 0, 0);

    gatt_cb.hdl_cfg.gatt_start_hdl = GATT_GATT_START_HANDLE;
    gatt_cb.hdl_cfg.gap_start_hdl  = GATT_GAP_START_HANDLE;
    gatt_cb.hdl_cfg.app_start_hdl  = GATT_APP_START_HANDLE;
#if (GATTS_INCLUDED == TRUE)
    gatt_profile_db_init();
#endif  ///GATTS_INCLUDED == TRUE
    //init local MTU size
    gatt_default.local_mtu = GATT_MAX_MTU_SIZE;
}