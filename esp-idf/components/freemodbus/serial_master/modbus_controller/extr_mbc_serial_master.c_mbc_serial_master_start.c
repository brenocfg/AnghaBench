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
struct TYPE_4__ {int /*<<< orphan*/  mbm_event_group; int /*<<< orphan*/  mbm_comm; } ;
typedef  TYPE_1__ mb_master_options_t ;
struct TYPE_5__ {scalar_t__ parity; scalar_t__ baudrate; scalar_t__ port; scalar_t__ mode; } ;
typedef  TYPE_2__ mb_communication_info_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  eMBParity ;
typedef  int /*<<< orphan*/  eMBMode ;
typedef  scalar_t__ eMBErrorCode ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_6__ {TYPE_1__ opts; } ;
typedef  int EventBits_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ MB_EIO ; 
 scalar_t__ MB_ENOERR ; 
 int MB_EVENT_STACK_STARTED ; 
 int /*<<< orphan*/  MB_MASTER_CHECK (int,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ eMBMasterEnable () ; 
 scalar_t__ eMBMasterInit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* mbm_interface_ptr ; 
 int xEventGroupSetBits (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static esp_err_t mbc_serial_master_start(void)
{
    MB_MASTER_CHECK((mbm_interface_ptr != NULL),
                    ESP_ERR_INVALID_STATE,
                    "Master interface uninitialized.");
    eMBErrorCode status = MB_EIO;
    mb_master_options_t* mbm_opts = &mbm_interface_ptr->opts;
    const mb_communication_info_t* comm_info = (mb_communication_info_t*)&mbm_opts->mbm_comm;

    // Initialize Modbus stack using mbcontroller parameters
    status = eMBMasterInit((eMBMode)comm_info->mode, (UCHAR)comm_info->port,
                            (ULONG)comm_info->baudrate, (eMBParity)comm_info->parity);
    MB_MASTER_CHECK((status == MB_ENOERR), ESP_ERR_INVALID_STATE,
            "mb stack initialization failure, eMBInit() returns (0x%x).", status);
    status = eMBMasterEnable();
    MB_MASTER_CHECK((status == MB_ENOERR), ESP_ERR_INVALID_STATE,
            "mb stack set slave ID failure, eMBEnable() returned (0x%x).", (uint32_t)status);
    // Set the mbcontroller start flag
    EventBits_t flag = xEventGroupSetBits(mbm_opts->mbm_event_group,
                                            (EventBits_t)MB_EVENT_STACK_STARTED);
    MB_MASTER_CHECK((flag & MB_EVENT_STACK_STARTED),
                ESP_ERR_INVALID_STATE, "mb stack start event set error.");
    return ESP_OK;
}