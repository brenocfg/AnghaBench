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
typedef  size_t UINT8 ;

/* Variables and functions */
 size_t GATT_CMD_WRITE ; 
 size_t GATT_OP_CODE_MAX ; 
 size_t GATT_SIGN_CMD_WRITE ; 
 size_t GATT_WRITE_CMD_MASK ; 
 scalar_t__* op_code_name ; 

UINT8 *gatt_dbg_op_name(UINT8 op_code)
{
    UINT8 pseduo_op_code_idx = op_code & (~GATT_WRITE_CMD_MASK);

    if (op_code == GATT_CMD_WRITE ) {
        pseduo_op_code_idx = 0x14; /* just an index to op_code_name */

    }

    if (op_code == GATT_SIGN_CMD_WRITE) {
        pseduo_op_code_idx = 0x15; /* just an index to op_code_name */
    }

    if (pseduo_op_code_idx <= GATT_OP_CODE_MAX) {
        return (UINT8 *) op_code_name[pseduo_op_code_idx];
    } else {
        return (UINT8 *)"Op Code Exceed Max";
    }
}