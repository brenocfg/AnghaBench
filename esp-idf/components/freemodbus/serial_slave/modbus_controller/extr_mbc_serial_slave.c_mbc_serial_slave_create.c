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
struct TYPE_5__ {int /*<<< orphan*/  parity; int /*<<< orphan*/  baudrate; int /*<<< orphan*/  port; int /*<<< orphan*/  slave_addr; int /*<<< orphan*/  mode; } ;
struct TYPE_6__ {int /*<<< orphan*/ * mbs_task_handle; int /*<<< orphan*/ * mbs_notification_queue_handle; int /*<<< orphan*/ * mbs_event_group; TYPE_1__ mbs_comm; scalar_t__ port_type; } ;
typedef  TYPE_2__ mb_slave_options_t ;
typedef  int /*<<< orphan*/  mb_slave_interface_t ;
typedef  scalar_t__ mb_port_type_t ;
typedef  int /*<<< orphan*/  mb_param_info_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_7__ {int /*<<< orphan*/  slave_reg_cb_coils; int /*<<< orphan*/  slave_reg_cb_holding; int /*<<< orphan*/  slave_reg_cb_input; int /*<<< orphan*/  slave_reg_cb_discrete; int /*<<< orphan*/  start; int /*<<< orphan*/  setup; int /*<<< orphan*/  set_descriptor; int /*<<< orphan*/  (* init ) (scalar_t__,void**) ;int /*<<< orphan*/  get_param_info; int /*<<< orphan*/  destroy; int /*<<< orphan*/  check_event; TYPE_2__ opts; } ;
typedef  scalar_t__ BaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  MB_CONTROLLER_NOTIFY_QUEUE_SIZE ; 
 int /*<<< orphan*/  MB_CONTROLLER_PRIORITY ; 
 int /*<<< orphan*/  MB_CONTROLLER_STACK_SIZE ; 
 int /*<<< orphan*/  MB_DEVICE_ADDRESS ; 
 int /*<<< orphan*/  MB_DEVICE_SPEED ; 
 int /*<<< orphan*/  MB_MODE_RTU ; 
 int /*<<< orphan*/  MB_PARITY_NONE ; 
 scalar_t__ MB_PORT_SERIAL_SLAVE ; 
 int /*<<< orphan*/  MB_SLAVE_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MB_SLAVE_CHECK (int,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  MB_UART_PORT ; 
 int /*<<< orphan*/  eMBRegCoilsCBSerialSlave ; 
 int /*<<< orphan*/  eMBRegDiscreteCBSerialSlave ; 
 int /*<<< orphan*/  eMBRegHoldingCBSerialSlave ; 
 int /*<<< orphan*/  eMBRegInputCBSerialSlave ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/  mbc_serial_slave_check_event ; 
 int /*<<< orphan*/  mbc_serial_slave_destroy ; 
 int /*<<< orphan*/  mbc_serial_slave_get_param_info ; 
 int /*<<< orphan*/  mbc_serial_slave_set_descriptor ; 
 int /*<<< orphan*/  mbc_serial_slave_setup ; 
 int /*<<< orphan*/  mbc_serial_slave_start ; 
 TYPE_3__* mbs_interface_ptr ; 
 int /*<<< orphan*/  modbus_slave_task ; 
 scalar_t__ pdPASS ; 
 int /*<<< orphan*/  vMBPortSetMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xEventGroupCreate () ; 
 int /*<<< orphan*/ * xQueueCreate (int /*<<< orphan*/ ,int) ; 
 scalar_t__ xTaskCreate (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

esp_err_t mbc_serial_slave_create(mb_port_type_t port_type, void** handler)
{
    MB_SLAVE_CHECK((port_type == MB_PORT_SERIAL_SLAVE), 
                    ESP_ERR_NOT_SUPPORTED, 
                    "mb port not supported = %u.", (uint32_t)port_type);
    // Allocate space for options
    if (mbs_interface_ptr == NULL) {
        mbs_interface_ptr = malloc(sizeof(mb_slave_interface_t));
    }
    MB_SLAVE_ASSERT(mbs_interface_ptr != NULL);
    vMBPortSetMode((UCHAR)port_type);
    mb_slave_options_t* mbs_opts = &mbs_interface_ptr->opts;
    mbs_opts->port_type = MB_PORT_SERIAL_SLAVE; // set interface port type

    // Set default values of communication options
    mbs_opts->mbs_comm.mode = MB_MODE_RTU;
    mbs_opts->mbs_comm.slave_addr = MB_DEVICE_ADDRESS;
    mbs_opts->mbs_comm.port = MB_UART_PORT;
    mbs_opts->mbs_comm.baudrate = MB_DEVICE_SPEED;
    mbs_opts->mbs_comm.parity = MB_PARITY_NONE;

    // Initialization of active context of the Modbus controller
    BaseType_t status = 0;
    // Parameter change notification queue
    mbs_opts->mbs_event_group = xEventGroupCreate();
    MB_SLAVE_CHECK((mbs_opts->mbs_event_group != NULL),
            ESP_ERR_NO_MEM, "mb event group error.");
    // Parameter change notification queue
    mbs_opts->mbs_notification_queue_handle = xQueueCreate(
                                                MB_CONTROLLER_NOTIFY_QUEUE_SIZE,
                                                sizeof(mb_param_info_t));
    MB_SLAVE_CHECK((mbs_opts->mbs_notification_queue_handle != NULL),
            ESP_ERR_NO_MEM, "mb notify queue creation error.");
    // Create Modbus controller task
    status = xTaskCreate((void*)&modbus_slave_task,
                            "modbus_slave_task",
                            MB_CONTROLLER_STACK_SIZE,
                            NULL,
                            MB_CONTROLLER_PRIORITY,
                            &mbs_opts->mbs_task_handle);
    if (status != pdPASS) {
        vTaskDelete(mbs_opts->mbs_task_handle);
        MB_SLAVE_CHECK((status == pdPASS), ESP_ERR_NO_MEM,
                "mb controller task creation error, xTaskCreate() returns (0x%x).",
                (uint32_t)status);
    }
    MB_SLAVE_ASSERT(mbs_opts->mbs_task_handle != NULL); // The task is created but handle is incorrect

    // Initialize interface function pointers
    mbs_interface_ptr->check_event = mbc_serial_slave_check_event;
    mbs_interface_ptr->destroy = mbc_serial_slave_destroy;
    mbs_interface_ptr->get_param_info = mbc_serial_slave_get_param_info;
    mbs_interface_ptr->init = mbc_serial_slave_create;
    mbs_interface_ptr->set_descriptor = mbc_serial_slave_set_descriptor;
    mbs_interface_ptr->setup = mbc_serial_slave_setup;
    mbs_interface_ptr->start = mbc_serial_slave_start;

    // Initialize stack callback function pointers
    mbs_interface_ptr->slave_reg_cb_discrete = eMBRegDiscreteCBSerialSlave;
    mbs_interface_ptr->slave_reg_cb_input = eMBRegInputCBSerialSlave;
    mbs_interface_ptr->slave_reg_cb_holding = eMBRegHoldingCBSerialSlave;
    mbs_interface_ptr->slave_reg_cb_coils = eMBRegCoilsCBSerialSlave;

    *handler = (void*)mbs_interface_ptr;

    return ESP_OK;
}