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
typedef  int tBTA_GATTC_INT_EVT ;

/* Variables and functions */
#define  BTA_GATTC_API_CACHE_CLEAN_EVT 151 
#define  BTA_GATTC_API_CANCEL_OPEN_EVT 150 
#define  BTA_GATTC_API_CFG_MTU_EVT 149 
#define  BTA_GATTC_API_CLOSE_EVT 148 
#define  BTA_GATTC_API_CONFIRM_EVT 147 
#define  BTA_GATTC_API_DEREG_EVT 146 
#define  BTA_GATTC_API_DISABLE_EVT 145 
#define  BTA_GATTC_API_EXEC_EVT 144 
#define  BTA_GATTC_API_LISTEN_EVT 143 
#define  BTA_GATTC_API_OPEN_EVT 142 
#define  BTA_GATTC_API_READ_EVT 141 
#define  BTA_GATTC_API_READ_MULTI_EVT 140 
#define  BTA_GATTC_API_REFRESH_EVT 139 
#define  BTA_GATTC_API_REG_EVT 138 
#define  BTA_GATTC_API_SEARCH_EVT 137 
#define  BTA_GATTC_API_WRITE_EVT 136 
#define  BTA_GATTC_DISCOVER_CMPL_EVT 135 
#define  BTA_GATTC_INT_CANCEL_OPEN_OK_EVT 134 
#define  BTA_GATTC_INT_CONN_EVT 133 
#define  BTA_GATTC_INT_DISCONN_EVT 132 
#define  BTA_GATTC_INT_DISCOVER_EVT 131 
#define  BTA_GATTC_INT_OPEN_FAIL_EVT 130 
#define  BTA_GATTC_INT_START_IF_EVT 129 
#define  BTA_GATTC_OP_CMPL_EVT 128 

__attribute__((used)) static char *gattc_evt_code(tBTA_GATTC_INT_EVT evt_code)
{
    switch (evt_code) {
    case BTA_GATTC_API_OPEN_EVT:
        return "BTA_GATTC_API_OPEN_EVT";
    case BTA_GATTC_INT_OPEN_FAIL_EVT:
        return "BTA_GATTC_INT_OPEN_FAIL_EVT";
    case BTA_GATTC_API_CANCEL_OPEN_EVT:
        return "BTA_GATTC_API_CANCEL_OPEN_EVT";
    case BTA_GATTC_INT_CANCEL_OPEN_OK_EVT:
        return "BTA_GATTC_INT_CANCEL_OPEN_OK_EVT";
    case BTA_GATTC_API_READ_EVT:
        return "BTA_GATTC_API_READ_EVT";
    case BTA_GATTC_API_WRITE_EVT:
        return "BTA_GATTC_API_WRITE_EVT";
    case BTA_GATTC_API_EXEC_EVT:
        return "BTA_GATTC_API_EXEC_EVT";
    case BTA_GATTC_API_CLOSE_EVT:
        return "BTA_GATTC_API_CLOSE_EVT";
    case BTA_GATTC_API_SEARCH_EVT:
        return "BTA_GATTC_API_SEARCH_EVT";
    case BTA_GATTC_API_CONFIRM_EVT:
        return "BTA_GATTC_API_CONFIRM_EVT";
    case BTA_GATTC_API_READ_MULTI_EVT:
        return "BTA_GATTC_API_READ_MULTI_EVT";
    case BTA_GATTC_INT_CONN_EVT:
        return "BTA_GATTC_INT_CONN_EVT";
    case BTA_GATTC_INT_DISCOVER_EVT:
        return "BTA_GATTC_INT_DISCOVER_EVT";
    case BTA_GATTC_DISCOVER_CMPL_EVT:
        return "BTA_GATTC_DISCOVER_CMPL_EVT";
    case BTA_GATTC_OP_CMPL_EVT:
        return "BTA_GATTC_OP_CMPL_EVT";
    case BTA_GATTC_INT_DISCONN_EVT:
        return "BTA_GATTC_INT_DISCONN_EVT";
    case BTA_GATTC_INT_START_IF_EVT:
        return "BTA_GATTC_INT_START_IF_EVT";
    case BTA_GATTC_API_REG_EVT:
        return "BTA_GATTC_API_REG_EVT";
    case BTA_GATTC_API_DEREG_EVT:
        return "BTA_GATTC_API_DEREG_EVT";
    case BTA_GATTC_API_REFRESH_EVT:
        return "BTA_GATTC_API_REFRESH_EVT";
    case BTA_GATTC_API_CACHE_CLEAN_EVT:
        return "BTA_GATTC_API_CACHE_CLEAN_EVT";
    case BTA_GATTC_API_LISTEN_EVT:
        return "BTA_GATTC_API_LISTEN_EVT";
    case BTA_GATTC_API_DISABLE_EVT:
        return "BTA_GATTC_API_DISABLE_EVT";
    case BTA_GATTC_API_CFG_MTU_EVT:
        return "BTA_GATTC_API_CFG_MTU_EVT";
    default:
        return "unknown GATTC event code";
    }
}