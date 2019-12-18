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
typedef  int /*<<< orphan*/  u8_t ;
typedef  int /*<<< orphan*/  tBTM_INQ_RESULTS ;

/* Variables and functions */
 int /*<<< orphan*/  bt_mesh_scan_result_callback ; 
 int /*<<< orphan*/  bt_mesh_scan_results_change_2_bta (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bt_mesh_scan_results_cb(tBTM_INQ_RESULTS *p_inq, u8_t *p_eir)
{
    bt_mesh_scan_results_change_2_bta(p_inq, p_eir, bt_mesh_scan_result_callback);
}