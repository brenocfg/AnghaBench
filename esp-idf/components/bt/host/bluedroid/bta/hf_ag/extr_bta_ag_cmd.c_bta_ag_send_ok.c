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
typedef  int /*<<< orphan*/  tBTA_AG_SCB ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_AG_RES_OK ; 
 int /*<<< orphan*/  bta_ag_send_result (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bta_ag_send_ok(tBTA_AG_SCB *p_scb)
{
    bta_ag_send_result(p_scb, BTA_AG_RES_OK, NULL, 0);
}