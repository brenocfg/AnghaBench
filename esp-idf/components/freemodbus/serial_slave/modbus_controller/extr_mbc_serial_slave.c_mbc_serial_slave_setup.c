#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  mbs_comm; } ;
typedef  TYPE_1__ mb_slave_options_t ;
struct TYPE_5__ {scalar_t__ mode; scalar_t__ slave_addr; scalar_t__ port; scalar_t__ parity; } ;
typedef  TYPE_2__ mb_slave_comm_info_t ;
typedef  int /*<<< orphan*/  mb_communication_info_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_6__ {TYPE_1__ opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ MB_ADDRESS_MAX ; 
 scalar_t__ MB_MODE_ASCII ; 
 scalar_t__ MB_MODE_RTU ; 
 int /*<<< orphan*/  MB_SLAVE_CHECK (int,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ UART_NUM_MAX ; 
 scalar_t__ UART_PARITY_EVEN ; 
 TYPE_3__* mbs_interface_ptr ; 

__attribute__((used)) static esp_err_t mbc_serial_slave_setup(void* comm_info)
{
    MB_SLAVE_CHECK((mbs_interface_ptr != NULL),
                    ESP_ERR_INVALID_STATE,
                    "Slave interface is not correctly initialized.");
    MB_SLAVE_CHECK((comm_info != NULL), ESP_ERR_INVALID_ARG,
                    "mb wrong communication settings.");
    mb_slave_options_t* mbs_opts = &mbs_interface_ptr->opts;
    mb_slave_comm_info_t* comm_settings = (mb_slave_comm_info_t*)comm_info;
    MB_SLAVE_CHECK(((comm_settings->mode == MB_MODE_RTU) || (comm_settings->mode == MB_MODE_ASCII)),
                ESP_ERR_INVALID_ARG, "mb incorrect mode = (0x%x).",
                (uint32_t)comm_settings->mode);
    MB_SLAVE_CHECK((comm_settings->slave_addr <= MB_ADDRESS_MAX),
                ESP_ERR_INVALID_ARG, "mb wrong slave address = (0x%x).",
                (uint32_t)comm_settings->slave_addr);
    MB_SLAVE_CHECK((comm_settings->port < UART_NUM_MAX), ESP_ERR_INVALID_ARG,
                "mb wrong port to set = (0x%x).", (uint32_t)comm_settings->port);
    MB_SLAVE_CHECK((comm_settings->parity <= UART_PARITY_EVEN), ESP_ERR_INVALID_ARG,
                "mb wrong parity option = (0x%x).", (uint32_t)comm_settings->parity);

    // Set communication options of the controller
    mbs_opts->mbs_comm = *(mb_communication_info_t*)comm_settings;
    return ESP_OK;
}