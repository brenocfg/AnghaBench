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
#define  BTA_AG_SCO_CLOSE_OP_ST 138 
#define  BTA_AG_SCO_CLOSE_XFER_ST 137 
#define  BTA_AG_SCO_CLOSING_ST 136 
#define  BTA_AG_SCO_CODEC_ST 135 
#define  BTA_AG_SCO_LISTEN_ST 134 
#define  BTA_AG_SCO_OPENING_ST 133 
#define  BTA_AG_SCO_OPEN_CL_ST 132 
#define  BTA_AG_SCO_OPEN_ST 131 
#define  BTA_AG_SCO_OPEN_XFER_ST 130 
#define  BTA_AG_SCO_SHUTDOWN_ST 129 
#define  BTA_AG_SCO_SHUTTING_ST 128 

__attribute__((used)) static char *bta_ag_sco_state_str(UINT8 state)
{
    switch (state)
    {
        case BTA_AG_SCO_SHUTDOWN_ST:
            return "Shutdown";
        case BTA_AG_SCO_LISTEN_ST:
            return "Listening";
#if (BTM_WBS_INCLUDED == TRUE )
        case BTA_AG_SCO_CODEC_ST:
            return "Codec Negotiation";
#endif
        case BTA_AG_SCO_OPENING_ST:
            return "Opening";
        case BTA_AG_SCO_OPEN_CL_ST:
            return "Open while closing";
        case BTA_AG_SCO_OPEN_XFER_ST:
            return "Opening while Transferring";
        case BTA_AG_SCO_OPEN_ST:
            return "Open";
        case BTA_AG_SCO_CLOSING_ST:
            return "Closing";
        case BTA_AG_SCO_CLOSE_OP_ST:
            return "Close while Opening";
        case BTA_AG_SCO_CLOSE_XFER_ST:
            return "Close while Transferring";
        case BTA_AG_SCO_SHUTTING_ST:
            return "Shutting Down";
        default:
            return "Unknown SCO State";
    }
}