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

/* Variables and functions */
 int /*<<< orphan*/  adv_data_sem ; 
 int /*<<< orphan*/  adv_enable_sem ; 
 int /*<<< orphan*/  adv_param_sem ; 
 int /*<<< orphan*/  osi_sem_new (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scan_enable_sem ; 
 int /*<<< orphan*/  scan_param_sem ; 

void btm_ble_sem_init(void)
{
    osi_sem_new(&adv_enable_sem, 1, 0);
    osi_sem_new(&adv_data_sem, 1, 0);
    osi_sem_new(&adv_param_sem, 1, 0);
    osi_sem_new(&scan_enable_sem, 1, 0);
    osi_sem_new(&scan_param_sem, 1, 0);
}