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
typedef  int /*<<< orphan*/  tGATT_CLCB ;

/* Variables and functions */
 int /*<<< orphan*/  GATT_SUCCESS ; 
 int /*<<< orphan*/  gatt_end_operation (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void gatt_process_handle_rsp(tGATT_CLCB *p_clcb)
{
    gatt_end_operation(p_clcb, GATT_SUCCESS, NULL);
}