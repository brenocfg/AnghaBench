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
#define  BTA_AG_SCO_CI_DATA_E 137 
#define  BTA_AG_SCO_CLOSE_E 136 
#define  BTA_AG_SCO_CN_DONE_E 135 
#define  BTA_AG_SCO_CONN_CLOSE_E 134 
#define  BTA_AG_SCO_CONN_OPEN_E 133 
#define  BTA_AG_SCO_LISTEN_E 132 
#define  BTA_AG_SCO_OPEN_E 131 
#define  BTA_AG_SCO_REOPEN_E 130 
#define  BTA_AG_SCO_SHUTDOWN_E 129 
#define  BTA_AG_SCO_XFER_E 128 

__attribute__((used)) static char *bta_ag_sco_evt_str(UINT8 event)
{
    switch (event)
    {
    case BTA_AG_SCO_LISTEN_E:
        return "Listen Request";
    case BTA_AG_SCO_OPEN_E:
        return "Open Request";
    case BTA_AG_SCO_XFER_E:
        return "Transfer Request";
#if (BTM_WBS_INCLUDED == TRUE )
    case BTA_AG_SCO_CN_DONE_E:
        return "Codec Negotiation Done";
    case BTA_AG_SCO_REOPEN_E:
        return "Reopen Request";
#endif
    case BTA_AG_SCO_CLOSE_E:
        return "Close Request";
    case BTA_AG_SCO_SHUTDOWN_E:
        return "Shutdown Request";
    case BTA_AG_SCO_CONN_OPEN_E:
        return "Opened";
    case BTA_AG_SCO_CONN_CLOSE_E:
        return "Closed";
    case BTA_AG_SCO_CI_DATA_E  :
        return "Sco Data";
    default:
        return "Unknown SCO Event";
    }
}