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
typedef  int UINT8 ;

/* Variables and functions */
 int GATT_CMD_WRITE ; 

UINT8 gatt_cmd_to_rsp_code (UINT8 cmd_code)
{
    UINT8   rsp_code  = 0;

    if (cmd_code > 1 && cmd_code != GATT_CMD_WRITE) {
        rsp_code = cmd_code + 1;
    }
    return rsp_code;
}