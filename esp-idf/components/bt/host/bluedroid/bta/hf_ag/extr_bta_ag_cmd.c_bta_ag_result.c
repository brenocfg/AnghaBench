#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ conn_service; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;
struct TYPE_8__ {int /*<<< orphan*/  api_result; } ;
typedef  TYPE_2__ tBTA_AG_DATA ;

/* Variables and functions */
 scalar_t__ BTA_AG_HSP ; 
 int /*<<< orphan*/  bta_ag_hfp_result (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_ag_hsp_result (TYPE_1__*,int /*<<< orphan*/ *) ; 

void bta_ag_result(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data)
{
    if (p_scb->conn_service == BTA_AG_HSP) {
        bta_ag_hsp_result(p_scb, &p_data->api_result);
    } else {
        bta_ag_hfp_result(p_scb, &p_data->api_result);
    }
}