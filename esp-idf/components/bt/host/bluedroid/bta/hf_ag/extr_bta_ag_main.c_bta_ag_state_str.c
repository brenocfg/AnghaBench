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
#define  BTA_AG_CLOSING_ST 131 
#define  BTA_AG_INIT_ST 130 
#define  BTA_AG_OPENING_ST 129 
#define  BTA_AG_OPEN_ST 128 

__attribute__((used)) static char *bta_ag_state_str(UINT8 state)
{
    switch (state) {
    case BTA_AG_INIT_ST:
        return "Initial";
    case BTA_AG_OPENING_ST:
        return "Opening";
    case BTA_AG_OPEN_ST:
        return "Open";
    case BTA_AG_CLOSING_ST:
        return "Closing";
    default:
        return "Unknown AG State";
    }
}