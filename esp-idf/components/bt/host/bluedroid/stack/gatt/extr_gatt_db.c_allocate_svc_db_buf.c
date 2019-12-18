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
struct TYPE_3__ {int /*<<< orphan*/  svc_buffer; int /*<<< orphan*/  mem_free; int /*<<< orphan*/ * p_free_mem; } ;
typedef  TYPE_1__ tGATT_SVC_DB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  BT_HDR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXED_QUEUE_MAX_TIMEOUT ; 
 int /*<<< orphan*/  GATT_DB_BUF_SIZE ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  GATT_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fixed_queue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ osi_calloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOLEAN allocate_svc_db_buf(tGATT_SVC_DB *p_db)
{
    BT_HDR  *p_buf;

    GATT_TRACE_DEBUG("allocate_svc_db_buf allocating extra buffer");

    if ((p_buf = (BT_HDR *)osi_calloc(GATT_DB_BUF_SIZE)) == NULL) {
        GATT_TRACE_ERROR("allocate_svc_db_buf failed, no resources");
        return FALSE;
    }

    p_db->p_free_mem    = (UINT8 *) p_buf;
    p_db->mem_free = GATT_DB_BUF_SIZE;

    fixed_queue_enqueue(p_db->svc_buffer, p_buf, FIXED_QUEUE_MAX_TIMEOUT);

    return TRUE;

}