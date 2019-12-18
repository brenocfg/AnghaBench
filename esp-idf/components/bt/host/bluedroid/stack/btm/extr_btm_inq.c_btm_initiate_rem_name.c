#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
struct TYPE_6__ {int clock_offset; int /*<<< orphan*/  page_scan_mode; int /*<<< orphan*/  page_scan_rep_mode; } ;
struct TYPE_7__ {TYPE_1__ results; } ;
typedef  TYPE_2__ tBTM_INQ_INFO ;
struct TYPE_8__ {scalar_t__ remname_active; int /*<<< orphan*/  rmt_name_timer_ent; int /*<<< orphan*/  remname_bda; int /*<<< orphan*/ * p_remname_cmpl_cb; } ;
typedef  TYPE_3__ tBTM_INQUIRY_VAR_ST ;
typedef  int /*<<< orphan*/  tBTM_CMPL_CB ;
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_9__ {TYPE_3__ btm_inq_vars; } ;
typedef  scalar_t__ BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  BTM_BUSY ; 
 int BTM_CLOCK_OFFSET_VALID ; 
 int /*<<< orphan*/  BTM_CMD_STARTED ; 
 int /*<<< orphan*/  BTM_ILLEGAL_VALUE ; 
 int /*<<< orphan*/  BTM_IsDeviceUp () ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 scalar_t__ BTM_RMT_NAME_EXT ; 
 scalar_t__ BTM_RMT_NAME_SEC ; 
 int /*<<< orphan*/  BTM_WRONG_MODE ; 
 int /*<<< orphan*/  BTU_TTYPE_BTM_RMT_NAME ; 
 int /*<<< orphan*/  HCI_MANDATARY_PAGE_SCAN_MODE ; 
 int /*<<< orphan*/  HCI_PAGE_SCAN_REP_MODE_R1 ; 
 scalar_t__ TRUE ; 
 TYPE_5__ btm_cb ; 
 scalar_t__ btsnd_hcic_rmt_name_req (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tBTM_STATUS btm_initiate_rem_name (BD_ADDR remote_bda, tBTM_INQ_INFO *p_cur,
                                    UINT8 origin, UINT32 timeout, tBTM_CMPL_CB *p_cb)
{
    tBTM_INQUIRY_VAR_ST *p_inq = &btm_cb.btm_inq_vars;
    BOOLEAN              cmd_ok;

    /*** Make sure the device is ready ***/
    if (!BTM_IsDeviceUp()) {
        return (BTM_WRONG_MODE);
    }

    if (origin == BTM_RMT_NAME_SEC) {
        cmd_ok = btsnd_hcic_rmt_name_req (remote_bda, HCI_PAGE_SCAN_REP_MODE_R1,
                                          HCI_MANDATARY_PAGE_SCAN_MODE, 0);
        if (cmd_ok) {
            return BTM_CMD_STARTED;
        } else {
            return BTM_NO_RESOURCES;
        }
    }
    /* Make sure there are no two remote name requests from external API in progress */
    else if (origin == BTM_RMT_NAME_EXT) {
        if (p_inq->remname_active) {
            return (BTM_BUSY);
        } else {
            /* If there is no remote name request running,call the callback function and start timer */
            p_inq->p_remname_cmpl_cb = p_cb;
            memcpy(p_inq->remname_bda, remote_bda, BD_ADDR_LEN);
            btu_start_timer (&p_inq->rmt_name_timer_ent,
                             BTU_TTYPE_BTM_RMT_NAME,
                             timeout);

            /* If the database entry exists for the device, use its clock offset */
            if (p_cur) {
                cmd_ok = btsnd_hcic_rmt_name_req (remote_bda,
                                                  p_cur->results.page_scan_rep_mode,
                                                  p_cur->results.page_scan_mode,
                                                  (UINT16)(p_cur->results.clock_offset |
                                                          BTM_CLOCK_OFFSET_VALID));
            } else { /* Otherwise use defaults and mark the clock offset as invalid */
                cmd_ok = btsnd_hcic_rmt_name_req (remote_bda, HCI_PAGE_SCAN_REP_MODE_R1,
                                                  HCI_MANDATARY_PAGE_SCAN_MODE, 0);
            }
            if (cmd_ok) {
                p_inq->remname_active = TRUE;
                return BTM_CMD_STARTED;
            } else {
                return BTM_NO_RESOURCES;
            }
        }
    } else {
        return BTM_ILLEGAL_VALUE;
    }
}