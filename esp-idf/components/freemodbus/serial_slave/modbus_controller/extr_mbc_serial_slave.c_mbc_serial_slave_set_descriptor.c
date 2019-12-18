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
struct TYPE_5__ {TYPE_2__* mbs_area_descriptors; } ;
typedef  TYPE_1__ mb_slave_options_t ;
struct TYPE_6__ {size_t type; scalar_t__ size; int /*<<< orphan*/ * address; } ;
typedef  TYPE_2__ mb_register_area_descriptor_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_7__ {TYPE_1__ opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ MB_INST_MAX_SIZE ; 
 scalar_t__ MB_INST_MIN_SIZE ; 
 size_t MB_PARAM_COUNT ; 
 size_t MB_PARAM_HOLDING ; 
 int /*<<< orphan*/  MB_SLAVE_CHECK (int,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__* mbs_interface_ptr ; 

esp_err_t mbc_serial_slave_set_descriptor(const mb_register_area_descriptor_t descr_info)
{
    MB_SLAVE_CHECK((mbs_interface_ptr != NULL),
                    ESP_ERR_INVALID_STATE,
                    "Slave interface is not correctly initialized.");
    mb_slave_options_t* mbs_opts = &mbs_interface_ptr->opts;
    MB_SLAVE_CHECK(((descr_info.type < MB_PARAM_COUNT) && (descr_info.type >= MB_PARAM_HOLDING)),
                ESP_ERR_INVALID_ARG, "mb incorrect modbus instance type = (0x%x).",
                (uint32_t)descr_info.type);
    MB_SLAVE_CHECK((descr_info.address != NULL),
                ESP_ERR_INVALID_ARG, "mb instance pointer is NULL.");
    MB_SLAVE_CHECK((descr_info.size >= MB_INST_MIN_SIZE) && (descr_info.size < (MB_INST_MAX_SIZE)),
                ESP_ERR_INVALID_ARG, "mb instance size is incorrect = (0x%x).",
                (uint32_t)descr_info.size);
    mbs_opts->mbs_area_descriptors[descr_info.type] = descr_info;
    return ESP_OK;
}