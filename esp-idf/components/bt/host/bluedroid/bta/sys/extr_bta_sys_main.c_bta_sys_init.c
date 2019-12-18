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
typedef  int /*<<< orphan*/  tBTM_DEV_STATUS_CB ;
typedef  int /*<<< orphan*/  tBTA_SYS_CB ;
typedef  int /*<<< orphan*/  data_free_fn ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_INITIAL_TRACE_LEVEL ; 
 int /*<<< orphan*/  BTA_ALARM_HASH_MAP_SIZE ; 
 int /*<<< orphan*/  BTA_ID_SYS ; 
 int /*<<< orphan*/  BTM_RegisterForDeviceStatusNotif (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appl_trace_level ; 
 int /*<<< orphan*/  bta_alarm_hash_map ; 
 int /*<<< orphan*/  bta_alarm_lock ; 
 int /*<<< orphan*/  bta_ar_init () ; 
 int /*<<< orphan*/  bta_sys_cb ; 
 int /*<<< orphan*/  bta_sys_hw_btm_cback ; 
 int /*<<< orphan*/  bta_sys_hw_reg ; 
 int /*<<< orphan*/  bta_sys_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_function_pointer ; 
 int /*<<< orphan*/  hash_map_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osi_alarm_free ; 
 int /*<<< orphan*/  osi_mutex_new (int /*<<< orphan*/ *) ; 

void bta_sys_init(void)
{
    memset(&bta_sys_cb, 0, sizeof(tBTA_SYS_CB));

    osi_mutex_new(&bta_alarm_lock);

    bta_alarm_hash_map = hash_map_new(BTA_ALARM_HASH_MAP_SIZE,
                                      hash_function_pointer, NULL, (data_free_fn)osi_alarm_free, NULL);

    appl_trace_level = APPL_INITIAL_TRACE_LEVEL;

    /* register BTA SYS message handler */
    bta_sys_register( BTA_ID_SYS,  &bta_sys_hw_reg);

    /* register for BTM notifications */
    BTM_RegisterForDeviceStatusNotif ((tBTM_DEV_STATUS_CB *)&bta_sys_hw_btm_cback );

#if( defined BTA_AR_INCLUDED ) && (BTA_AR_INCLUDED == TRUE)
    bta_ar_init();
#endif

}