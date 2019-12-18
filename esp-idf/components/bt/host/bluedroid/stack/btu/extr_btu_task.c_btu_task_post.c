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
typedef  int uint32_t ;

/* Variables and functions */
#define  SIG_BTU_BTA_ALARM 134 
#define  SIG_BTU_BTA_MSG 133 
#define  SIG_BTU_GENERAL_ALARM 132 
#define  SIG_BTU_HCI_MSG 131 
#define  SIG_BTU_L2CAP_ALARM 130 
#define  SIG_BTU_ONESHOT_ALARM 129 
#define  SIG_BTU_START_UP 128 
 int /*<<< orphan*/  bta_sys_event ; 
 int /*<<< orphan*/  btu_bta_alarm_process ; 
 int /*<<< orphan*/  btu_general_alarm_process ; 
 int /*<<< orphan*/  btu_hci_msg_process ; 
 int /*<<< orphan*/  btu_l2cap_alarm_process ; 
 int /*<<< orphan*/  btu_task_start_up ; 
 int /*<<< orphan*/  btu_thread ; 
 int osi_thread_post (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 

bool btu_task_post(uint32_t sig, void *param, uint32_t timeout)
{
    bool status = false;

    switch (sig) {
        case SIG_BTU_START_UP:
            status = osi_thread_post(btu_thread, btu_task_start_up, param, 0, timeout);
            break;
        case SIG_BTU_HCI_MSG:
            status = osi_thread_post(btu_thread, btu_hci_msg_process, param, 0, timeout);
            break;
#if (defined(BTA_INCLUDED) && BTA_INCLUDED == TRUE)
        case SIG_BTU_BTA_MSG:
            status = osi_thread_post(btu_thread, bta_sys_event, param, 0, timeout);
            break;
        case SIG_BTU_BTA_ALARM:
            status = osi_thread_post(btu_thread, btu_bta_alarm_process, param, 0, timeout);
            break;
#endif
        case SIG_BTU_GENERAL_ALARM:
        case SIG_BTU_ONESHOT_ALARM:
            status = osi_thread_post(btu_thread, btu_general_alarm_process, param, 0, timeout);
            break;
        case SIG_BTU_L2CAP_ALARM:
            status = osi_thread_post(btu_thread, btu_l2cap_alarm_process, param, 0, timeout);
            break;
        default:
            break;
    }

    return status;
}