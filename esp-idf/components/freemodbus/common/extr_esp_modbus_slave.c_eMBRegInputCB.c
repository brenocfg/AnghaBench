#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  eMBErrorCode ;
typedef  int /*<<< orphan*/  USHORT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_2__ {int /*<<< orphan*/  (* slave_reg_cb_input ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  MB_ENOERR ; 
 int /*<<< orphan*/  MB_SLAVE_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* slave_interface_ptr ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

eMBErrorCode eMBRegInputCB(UCHAR * pucRegBuffer, USHORT usAddress,
                                USHORT usNRegs)
{
    eMBErrorCode error = MB_ENOERR;
    MB_SLAVE_CHECK((slave_interface_ptr != NULL),
                    ESP_ERR_INVALID_STATE,
                    "Slave interface is not correctly initialized.");
    MB_SLAVE_CHECK((slave_interface_ptr->slave_reg_cb_input != NULL), 
                    ESP_ERR_INVALID_STATE,
                    "Slave interface is not correctly initialized.");
    error = slave_interface_ptr->slave_reg_cb_input(pucRegBuffer, usAddress, usNRegs);
    return error;
}