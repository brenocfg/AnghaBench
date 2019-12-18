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
struct TYPE_5__ {int /*<<< orphan*/  svc_buffer; } ;
struct TYPE_6__ {TYPE_1__ svc_db; } ;
typedef  TYPE_2__ tGATT_HDL_LIST_ELEM ;

/* Variables and functions */
 int /*<<< orphan*/  fixed_queue_dequeue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixed_queue_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fixed_queue_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ ) ; 

void gatt_free_hdl_buffer(tGATT_HDL_LIST_ELEM *p)
{

    if (p) {
        while (!fixed_queue_is_empty(p->svc_db.svc_buffer)) {
            osi_free(fixed_queue_dequeue(p->svc_db.svc_buffer, 0));
		}
        fixed_queue_free(p->svc_db.svc_buffer, NULL);
        memset(p, 0, sizeof(tGATT_HDL_LIST_ELEM));
    }
}