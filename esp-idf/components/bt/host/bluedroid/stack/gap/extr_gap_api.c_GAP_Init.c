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
typedef  int /*<<< orphan*/  tGAP_CB ;
typedef  int /*<<< orphan*/  bt_status_t ;
struct TYPE_3__ {int /*<<< orphan*/  trace_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_STATUS_NOMEM ; 
 int /*<<< orphan*/  BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  BT_TRACE_LEVEL_NONE ; 
 int /*<<< orphan*/  GAP_INITIAL_TRACE_LEVEL ; 
 int /*<<< orphan*/  gap_attr_db_init () ; 
 TYPE_1__ gap_cb ; 
 int /*<<< orphan*/ * gap_cb_ptr ; 
 int /*<<< orphan*/  gap_conn_init () ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osi_malloc (int) ; 

bt_status_t GAP_Init(void)
{
#if GAP_DYNAMIC_MEMORY == TRUE
    gap_cb_ptr = (tGAP_CB *)osi_malloc(sizeof(tGAP_CB));
    if (!gap_cb_ptr) {
        return BT_STATUS_NOMEM;
    }
#endif

    memset (&gap_cb, 0, sizeof (tGAP_CB));

#if defined(GAP_INITIAL_TRACE_LEVEL)
    gap_cb.trace_level = GAP_INITIAL_TRACE_LEVEL;
#else
    gap_cb.trace_level = BT_TRACE_LEVEL_NONE;    /* No traces */
#endif

#if GAP_CONN_INCLUDED == TRUE
    gap_conn_init();
#endif

#if BLE_INCLUDED == TRUE && GATTS_INCLUDED == TRUE
    gap_attr_db_init();
#endif

    return BT_STATUS_SUCCESS;
}