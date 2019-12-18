#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* serv_handle; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;
typedef  size_t UINT8 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 size_t BTA_AG_NUM_IDX ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN bta_ag_is_server_closed (tBTA_AG_SCB *p_scb)
{
    UINT8 i;
    BOOLEAN is_closed = TRUE;

    for (i = 0; i < BTA_AG_NUM_IDX; i++) {
        if (p_scb->serv_handle[i] != 0)
            is_closed = FALSE;
    }
    return is_closed;
}