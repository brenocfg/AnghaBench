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
typedef  int tBTA_SERVICE_MASK ;
struct TYPE_3__ {scalar_t__* serv_handle; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;

/* Variables and functions */
 int BTA_AG_NUM_IDX ; 
 int BTA_HSP_SERVICE_ID ; 
 int /*<<< orphan*/  RFCOMM_RemoveServer (scalar_t__) ; 

void bta_ag_close_servers(tBTA_AG_SCB *p_scb, tBTA_SERVICE_MASK services)
{
    int i;

    services >>= BTA_HSP_SERVICE_ID;
    for (i = 0; i < BTA_AG_NUM_IDX && services != 0; i++, services >>= 1) {
        /* if service is set in mask */
        if (services & 1) {
            RFCOMM_RemoveServer(p_scb->serv_handle[i]);
            p_scb->serv_handle[i] = 0;
        }
    }
}