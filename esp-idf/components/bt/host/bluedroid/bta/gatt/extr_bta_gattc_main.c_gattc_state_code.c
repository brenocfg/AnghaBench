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
typedef  int tBTA_GATTC_STATE ;

/* Variables and functions */
#define  BTA_GATTC_CONN_ST 131 
#define  BTA_GATTC_DISCOVER_ST 130 
#define  BTA_GATTC_IDLE_ST 129 
#define  BTA_GATTC_W4_CONN_ST 128 

__attribute__((used)) static char *gattc_state_code(tBTA_GATTC_STATE state_code)
{
    switch (state_code) {
    case BTA_GATTC_IDLE_ST:
        return "GATTC_IDLE_ST";
    case BTA_GATTC_W4_CONN_ST:
        return "GATTC_W4_CONN_ST";
    case BTA_GATTC_CONN_ST:
        return "GATTC_CONN_ST";
    case BTA_GATTC_DISCOVER_ST:
        return "GATTC_DISCOVER_ST";
    default:
        return "unknown GATTC state code";
    }
}