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
struct TYPE_4__ {int /*<<< orphan*/  mbm_comm; } ;
typedef  TYPE_1__ mb_master_options_t ;
struct TYPE_5__ {scalar_t__ mode; scalar_t__ port; scalar_t__ parity; } ;
typedef  TYPE_2__ mb_master_comm_info_t ;
typedef  int /*<<< orphan*/  mb_communication_info_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_6__ {TYPE_1__ opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  MB_MASTER_CHECK (int,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ MB_MODE_ASCII ; 
 scalar_t__ MB_MODE_RTU ; 
 scalar_t__ UART_NUM_MAX ; 
 scalar_t__ UART_PARITY_EVEN ; 
 TYPE_3__* mbm_interface_ptr ; 

__attribute__((used)) static esp_err_t mbc_serial_master_setup(void* comm_info)
{
    MB_MASTER_CHECK((mbm_interface_ptr != NULL),
                    ESP_ERR_INVALID_STATE,
                    "Master interface uninitialized.");
    mb_master_options_t* mbm_opts = &mbm_interface_ptr->opts;

    const mb_master_comm_info_t* comm_info_ptr = (mb_master_comm_info_t*)comm_info;
    // Check communication options
    MB_MASTER_CHECK(((comm_info_ptr->mode == MB_MODE_RTU) || (comm_info_ptr->mode == MB_MODE_ASCII)),
                ESP_ERR_INVALID_ARG, "mb incorrect mode = (0x%x).",
                (uint32_t)comm_info_ptr->mode);
    MB_MASTER_CHECK((comm_info_ptr->port < UART_NUM_MAX), ESP_ERR_INVALID_ARG,
                "mb wrong port to set = (0x%x).", (uint32_t)comm_info_ptr->port);
    MB_MASTER_CHECK((comm_info_ptr->parity <= UART_PARITY_EVEN), ESP_ERR_INVALID_ARG,
                "mb wrong parity option = (0x%x).", (uint32_t)comm_info_ptr->parity);
    // Save the communication options
    mbm_opts->mbm_comm = *(mb_communication_info_t*)comm_info_ptr;
    return ESP_OK;
}