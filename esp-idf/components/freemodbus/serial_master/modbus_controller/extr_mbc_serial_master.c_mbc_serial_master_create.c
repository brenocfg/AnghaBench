#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ mb_port_type_t ;
struct TYPE_5__ {int /*<<< orphan*/  parity; int /*<<< orphan*/  baudrate; int /*<<< orphan*/  port; int /*<<< orphan*/  mode; } ;
struct TYPE_6__ {int /*<<< orphan*/ * mbm_task_handle; int /*<<< orphan*/ * mbm_event_group; TYPE_1__ mbm_comm; scalar_t__ port_type; } ;
typedef  TYPE_2__ mb_master_options_t ;
typedef  int /*<<< orphan*/  mb_master_interface_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_7__ {int /*<<< orphan*/  master_reg_cb_coils; int /*<<< orphan*/  master_reg_cb_holding; int /*<<< orphan*/  master_reg_cb_input; int /*<<< orphan*/  master_reg_cb_discrete; int /*<<< orphan*/  set_parameter; int /*<<< orphan*/  set_descriptor; int /*<<< orphan*/  send_request; int /*<<< orphan*/  get_parameter; int /*<<< orphan*/  get_cid_info; int /*<<< orphan*/  start; int /*<<< orphan*/  setup; int /*<<< orphan*/  destroy; int /*<<< orphan*/  (* init ) (scalar_t__,void**) ;TYPE_2__ opts; } ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  MB_CONTROLLER_PRIORITY ; 
 int /*<<< orphan*/  MB_CONTROLLER_STACK_SIZE ; 
 int /*<<< orphan*/  MB_DEVICE_SPEED ; 
 int /*<<< orphan*/  MB_MASTER_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MB_MASTER_CHECK (int,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  MB_MODE_RTU ; 
 int /*<<< orphan*/  MB_PARITY_NONE ; 
 scalar_t__ MB_PORT_SERIAL_MASTER ; 
 int /*<<< orphan*/  MB_UART_PORT ; 
 int /*<<< orphan*/  eMBRegCoilsCBSerialMaster ; 
 int /*<<< orphan*/  eMBRegDiscreteCBSerialMaster ; 
 int /*<<< orphan*/  eMBRegHoldingCBSerialMaster ; 
 int /*<<< orphan*/  eMBRegInputCBSerialMaster ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/  mbc_serial_master_destroy ; 
 int /*<<< orphan*/  mbc_serial_master_get_cid_info ; 
 int /*<<< orphan*/  mbc_serial_master_get_parameter ; 
 int /*<<< orphan*/  mbc_serial_master_send_request ; 
 int /*<<< orphan*/  mbc_serial_master_set_descriptor ; 
 int /*<<< orphan*/  mbc_serial_master_set_parameter ; 
 int /*<<< orphan*/  mbc_serial_master_setup ; 
 int /*<<< orphan*/  mbc_serial_master_start ; 
 TYPE_3__* mbm_interface_ptr ; 
 int /*<<< orphan*/  modbus_master_task ; 
 scalar_t__ pdPASS ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xEventGroupCreate () ; 
 scalar_t__ xTaskCreate (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

esp_err_t mbc_serial_master_create(mb_port_type_t port_type, void** handler)
{
    MB_MASTER_CHECK((port_type == MB_PORT_SERIAL_MASTER), 
                        ESP_ERR_INVALID_STATE, "mb incorrect port selected = %u.", 
                        (uint32_t)port_type);
    // Allocate space for master interface structure
    if (mbm_interface_ptr == NULL) {
        mbm_interface_ptr = malloc(sizeof(mb_master_interface_t));
    }
    MB_MASTER_ASSERT(mbm_interface_ptr != NULL);

    // Initialize interface properties
    mb_master_options_t* mbm_opts = &mbm_interface_ptr->opts;
    mbm_opts->port_type = MB_PORT_SERIAL_MASTER;

    mbm_opts->mbm_comm.mode = MB_MODE_RTU;
    mbm_opts->mbm_comm.port = MB_UART_PORT;
    mbm_opts->mbm_comm.baudrate = MB_DEVICE_SPEED;
    mbm_opts->mbm_comm.parity = MB_PARITY_NONE;

    // Initialization of active context of the modbus controller
    BaseType_t status = 0;
    // Parameter change notification queue
    mbm_opts->mbm_event_group = xEventGroupCreate();
    MB_MASTER_CHECK((mbm_opts->mbm_event_group != NULL), 
                        ESP_ERR_NO_MEM, "mb event group error.");
    // Create modbus controller task
    status = xTaskCreate((void*)&modbus_master_task,
                            "modbus_matask",
                            MB_CONTROLLER_STACK_SIZE,
                            NULL,                       // No parameters
                            MB_CONTROLLER_PRIORITY,
                            &mbm_opts->mbm_task_handle);
    if (status != pdPASS) {
        vTaskDelete(mbm_opts->mbm_task_handle);
        MB_MASTER_CHECK((status == pdPASS), ESP_ERR_NO_MEM,
                "mb controller task creation error, xTaskCreate() returns (0x%x).",
                (uint32_t)status);
    }
    MB_MASTER_ASSERT(mbm_opts->mbm_task_handle != NULL); // The task is created but handle is incorrect

    // Initialize public interface methods of the interface
    mbm_interface_ptr->init = mbc_serial_master_create;
    mbm_interface_ptr->destroy = mbc_serial_master_destroy;
    mbm_interface_ptr->setup = mbc_serial_master_setup;
    mbm_interface_ptr->start = mbc_serial_master_start;
    mbm_interface_ptr->get_cid_info = mbc_serial_master_get_cid_info;
    mbm_interface_ptr->get_parameter = mbc_serial_master_get_parameter;
    mbm_interface_ptr->send_request = mbc_serial_master_send_request;
    mbm_interface_ptr->set_descriptor = mbc_serial_master_set_descriptor;
    mbm_interface_ptr->set_parameter = mbc_serial_master_set_parameter;

    mbm_interface_ptr->master_reg_cb_discrete = eMBRegDiscreteCBSerialMaster;
    mbm_interface_ptr->master_reg_cb_input = eMBRegInputCBSerialMaster;
    mbm_interface_ptr->master_reg_cb_holding = eMBRegHoldingCBSerialMaster;
    mbm_interface_ptr->master_reg_cb_coils = eMBRegCoilsCBSerialMaster;

    *handler = mbm_interface_ptr;

    return ESP_OK;
}