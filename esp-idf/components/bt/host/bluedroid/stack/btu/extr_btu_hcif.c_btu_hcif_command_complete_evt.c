#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int command_opcode_t ;
struct TYPE_6__ {void* context; TYPE_2__* response; int /*<<< orphan*/  callback; } ;
typedef  TYPE_1__ command_complete_hack_t ;
struct TYPE_7__ {void** data; int offset; int /*<<< orphan*/  event; } ;
typedef  TYPE_2__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTU_POST_TO_TASK_NO_GOOD_HORRIBLE_HACK ; 
#define  HCI_BLE_WRITE_ADV_DATA 133 
#define  HCI_BLE_WRITE_ADV_ENABLE 132 
#define  HCI_BLE_WRITE_ADV_PARAMS 131 
#define  HCI_BLE_WRITE_SCAN_ENABLE 130 
#define  HCI_BLE_WRITE_SCAN_PARAMS 129 
#define  HCI_BLE_WRITE_SCAN_RSP_DATA 128 
 int /*<<< orphan*/  HCI_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  OSI_THREAD_MAX_TIMEOUT ; 
 int /*<<< orphan*/  SIG_BTU_HCI_MSG ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (int,void**) ; 
 int /*<<< orphan*/  adv_data_sem ; 
 void* adv_data_status ; 
 int /*<<< orphan*/  adv_enable_sem ; 
 void* adv_enable_status ; 
 int /*<<< orphan*/  adv_param_sem ; 
 void* adv_param_status ; 
 int /*<<< orphan*/  btu_hcif_command_complete_evt_on_task ; 
 int /*<<< orphan*/  btu_task_post (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* osi_calloc (int) ; 
 int /*<<< orphan*/  osi_sem_give (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scan_enable_sem ; 
 void* scan_enable_status ; 
 int /*<<< orphan*/  scan_param_sem ; 
 void* scan_param_status ; 

__attribute__((used)) static void btu_hcif_command_complete_evt(BT_HDR *response, void *context)
{
#if (BLE_INCLUDED == TRUE)
    command_opcode_t opcode;
    uint8_t *stream = response->data + response->offset + 3;
    STREAM_TO_UINT16(opcode, stream);
    switch (opcode) {
        case HCI_BLE_WRITE_ADV_DATA:
            adv_data_status = *stream;
            osi_sem_give(&adv_data_sem);
            break;
        case HCI_BLE_WRITE_SCAN_RSP_DATA:
            adv_data_status = *stream;
            osi_sem_give(&adv_data_sem);
            break;
        case HCI_BLE_WRITE_ADV_ENABLE: {
            adv_enable_status = *stream;
            osi_sem_give(&adv_enable_sem);
            break;
        }
        case HCI_BLE_WRITE_ADV_PARAMS:
            adv_param_status = *stream;
            osi_sem_give(&adv_param_sem);
            break;
        case HCI_BLE_WRITE_SCAN_PARAMS:
            scan_param_status = *stream;
            osi_sem_give(&scan_param_sem);
            break;
        case HCI_BLE_WRITE_SCAN_ENABLE:
            scan_enable_status = *stream;
            osi_sem_give(&scan_enable_sem);
            break;
        default:
            break;
    }
#endif
    BT_HDR *event = osi_calloc(sizeof(BT_HDR) + sizeof(command_complete_hack_t));
    command_complete_hack_t *hack = (command_complete_hack_t *)&event->data[0];

    HCI_TRACE_DEBUG("btu_hcif_command_complete_evt\n");

    hack->callback = btu_hcif_command_complete_evt_on_task;
    hack->response = response;
    hack->context = context;

    event->event = BTU_POST_TO_TASK_NO_GOOD_HORRIBLE_HACK;

    btu_task_post(SIG_BTU_HCI_MSG, event, OSI_THREAD_MAX_TIMEOUT);
}