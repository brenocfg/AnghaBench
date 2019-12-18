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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ mb_port_type_t ;
typedef  int /*<<< orphan*/  mb_master_interface_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 scalar_t__ ESP_ERR_NOT_SUPPORTED ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  MB_MASTER_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
#define  MB_PORT_SERIAL_MASTER 129 
#define  MB_PORT_TCP_MASTER 128 
 int /*<<< orphan*/ * master_interface_ptr ; 
 scalar_t__ mbc_serial_master_create (scalar_t__,void**) ; 

esp_err_t mbc_master_init(mb_port_type_t port_type, void** handler)
{
    void* port_handler = NULL;
    esp_err_t error = ESP_ERR_NOT_SUPPORTED;
    switch(port_type)
    {
    case MB_PORT_SERIAL_MASTER:
        error = mbc_serial_master_create(port_type, &port_handler);
        break;
    case MB_PORT_TCP_MASTER:
        // TCP MAster is not yet supported
        //error = mbc_tcp_master_create(port_type, &port_handler);
        return ESP_ERR_NOT_SUPPORTED;
    default:
        return ESP_ERR_NOT_SUPPORTED;
    }
    MB_MASTER_CHECK((port_handler != NULL),
                    ESP_ERR_INVALID_STATE,
                    "Master interface initialization failure, error=(0x%x), port type=(0x%x).",
                    error, (uint16_t)port_type);

    if ((port_handler != NULL) && (error == ESP_OK)) {
        master_interface_ptr = (mb_master_interface_t*) port_handler;
        *handler = port_handler;
    }
    
    return  error;
}