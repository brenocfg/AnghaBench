#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * p_new_srv_start; } ;
typedef  TYPE_1__ tGATTS_PENDING_NEW_SRV_START ;
typedef  int /*<<< orphan*/  tGATTS_HNDL_RANGE ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_6__ {int /*<<< orphan*/  pending_new_srv_start_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIXED_QUEUE_MAX_TIMEOUT ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  fixed_queue_enqueue (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__ gatt_cb ; 
 scalar_t__ osi_malloc (int /*<<< orphan*/ ) ; 

tGATTS_PENDING_NEW_SRV_START *gatt_add_pending_new_srv_start(tGATTS_HNDL_RANGE *p_new_srv_start)
{
    tGATTS_PENDING_NEW_SRV_START   *p_buf;

    GATT_TRACE_DEBUG ("gatt_add_pending_new_srv_start");
    if ((p_buf = (tGATTS_PENDING_NEW_SRV_START *)osi_malloc((UINT16)sizeof(tGATTS_PENDING_NEW_SRV_START))) != NULL) {
        GATT_TRACE_DEBUG ("enqueue a new pending new srv start");
        p_buf->p_new_srv_start = p_new_srv_start;
    fixed_queue_enqueue(gatt_cb.pending_new_srv_start_q, p_buf, FIXED_QUEUE_MAX_TIMEOUT);
    }
    return p_buf;
}