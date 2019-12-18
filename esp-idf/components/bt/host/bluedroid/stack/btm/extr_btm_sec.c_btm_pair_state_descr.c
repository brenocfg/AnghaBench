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
typedef  int tBTM_PAIRING_STATE ;
struct TYPE_2__ {char* state_temp_buffer; } ;

/* Variables and functions */
#define  BTM_PAIR_STATE_GET_REM_NAME 138 
#define  BTM_PAIR_STATE_IDLE 137 
#define  BTM_PAIR_STATE_INCOMING_SSP 136 
#define  BTM_PAIR_STATE_KEY_ENTRY 135 
#define  BTM_PAIR_STATE_WAIT_AUTH_COMPLETE 134 
#define  BTM_PAIR_STATE_WAIT_DISCONNECT 133 
#define  BTM_PAIR_STATE_WAIT_LOCAL_IOCAPS 132 
#define  BTM_PAIR_STATE_WAIT_LOCAL_OOB_RSP 131 
#define  BTM_PAIR_STATE_WAIT_LOCAL_PIN 130 
#define  BTM_PAIR_STATE_WAIT_NUMERIC_CONFIRM 129 
#define  BTM_PAIR_STATE_WAIT_PIN_REQ 128 
 TYPE_1__ btm_cb ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static char *btm_pair_state_descr (tBTM_PAIRING_STATE state)
{
#if (BT_TRACE_VERBOSE == TRUE)
    switch (state) {
    case BTM_PAIR_STATE_IDLE:                   return ("IDLE");
    case BTM_PAIR_STATE_GET_REM_NAME:           return ("GET_REM_NAME");
    case BTM_PAIR_STATE_WAIT_PIN_REQ:           return ("WAIT_PIN_REQ");
    case BTM_PAIR_STATE_WAIT_LOCAL_PIN:         return ("WAIT_LOCAL_PIN");
    case BTM_PAIR_STATE_WAIT_NUMERIC_CONFIRM:   return ("WAIT_NUM_CONFIRM");
    case BTM_PAIR_STATE_KEY_ENTRY:              return ("KEY_ENTRY");
    case BTM_PAIR_STATE_WAIT_LOCAL_OOB_RSP:     return ("WAIT_LOCAL_OOB_RSP");
    case BTM_PAIR_STATE_WAIT_LOCAL_IOCAPS:      return ("WAIT_LOCAL_IOCAPS");
    case BTM_PAIR_STATE_INCOMING_SSP:           return ("INCOMING_SSP");
    case BTM_PAIR_STATE_WAIT_AUTH_COMPLETE:     return ("WAIT_AUTH_COMPLETE");
    case BTM_PAIR_STATE_WAIT_DISCONNECT:        return ("WAIT_DISCONNECT");
    }

    return ("???");
#else
    sprintf(btm_cb.state_temp_buffer, "%d", state);

    return (btm_cb.state_temp_buffer);
#endif
}