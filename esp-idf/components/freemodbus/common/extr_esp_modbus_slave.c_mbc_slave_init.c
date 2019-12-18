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
typedef  int /*<<< orphan*/  mb_slave_interface_t ;
typedef  scalar_t__ mb_port_type_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 scalar_t__ ESP_ERR_NOT_SUPPORTED ; 
 scalar_t__ ESP_OK ; 
#define  MB_PORT_SERIAL_SLAVE 129 
#define  MB_PORT_TCP_SLAVE 128 
 int /*<<< orphan*/  MB_SLAVE_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mbc_serial_slave_create (scalar_t__,void**) ; 
 int /*<<< orphan*/ * slave_interface_ptr ; 

esp_err_t mbc_slave_init(mb_port_type_t port_type, void** handler)
{
    void* port_handler = NULL;
    esp_err_t error = ESP_ERR_NOT_SUPPORTED;
    switch(port_type)
    {
        case MB_PORT_SERIAL_SLAVE:
            // Call constructor function of actual port implementation
            error = mbc_serial_slave_create(port_type, &port_handler);
            break;
        case MB_PORT_TCP_SLAVE:
            // Not yet supported
            //error = mbc_tcp_slave_create(port_type, &port_handler);
            return ESP_ERR_NOT_SUPPORTED;
        default:
            return ESP_ERR_NOT_SUPPORTED;
    }
    MB_SLAVE_CHECK((port_handler != NULL),
                    ESP_ERR_INVALID_STATE,
                    "Slave interface initialization failure, error=(0x%x), port type=(0x%x).",
                    error, (uint16_t)port_type);

    if ((port_handler != NULL) && (error == ESP_OK)) {
        slave_interface_ptr = (mb_slave_interface_t*) port_handler;
        *handler = port_handler;
    }
    
    return error;
}