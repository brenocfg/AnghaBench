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
typedef  int tBTM_STATUS ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
#define  BTM_BUSY 135 
#define  BTM_CMD_STARTED 134 
#define  BTM_DEVICE_TIMEOUT 133 
#define  BTM_ILLEGAL_VALUE 132 
#define  BTM_MODE_UNSUPPORTED 131 
#define  BTM_SUCCESS 130 
#define  BTM_UNKNOWN_ADDR 129 
#define  BTM_WRONG_MODE 128 
 int /*<<< orphan*/  BT_PASS ; 
 int /*<<< orphan*/  GAP_BAD_BD_ADDR ; 
 int /*<<< orphan*/  GAP_CMD_INITIATED ; 
 int /*<<< orphan*/  GAP_DEVICE_NOT_UP ; 
 int /*<<< orphan*/  GAP_ERR_BUSY ; 
 int /*<<< orphan*/  GAP_ERR_ILL_PARM ; 
 int /*<<< orphan*/  GAP_ERR_PROCESSING ; 
 int /*<<< orphan*/  GAP_ERR_TIMEOUT ; 

UINT16 gap_convert_btm_status (tBTM_STATUS btm_status)
{
    switch (btm_status) {
    case BTM_SUCCESS:
        return (BT_PASS);

    case BTM_CMD_STARTED:
        return (GAP_CMD_INITIATED);

    case BTM_BUSY:
        return (GAP_ERR_BUSY);

    case BTM_MODE_UNSUPPORTED:
    case BTM_ILLEGAL_VALUE:
        return (GAP_ERR_ILL_PARM);

    case BTM_WRONG_MODE:
        return (GAP_DEVICE_NOT_UP);

    case BTM_UNKNOWN_ADDR:
        return (GAP_BAD_BD_ADDR);

    case BTM_DEVICE_TIMEOUT:
        return (GAP_ERR_TIMEOUT);

    default:
        return (GAP_ERR_PROCESSING);
    }
}