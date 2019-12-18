#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ conn_service; scalar_t__ cmee_enabled; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;
typedef  int /*<<< orphan*/  INT16 ;

/* Variables and functions */
 scalar_t__ BTA_AG_HFP ; 
 int /*<<< orphan*/  BTA_AG_RES_CMEE ; 
 int /*<<< orphan*/  BTA_AG_RES_ERROR ; 
 int /*<<< orphan*/  bta_ag_send_result (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bta_ag_send_error(tBTA_AG_SCB *p_scb, INT16 errcode)
{
    /* If HFP and extended audio gateway error codes are enabled */
    if (p_scb->conn_service == BTA_AG_HFP && p_scb->cmee_enabled) {
        bta_ag_send_result(p_scb, BTA_AG_RES_CMEE, NULL, errcode);
    } else {
        bta_ag_send_result(p_scb, BTA_AG_RES_ERROR, NULL, 0);
    }
}