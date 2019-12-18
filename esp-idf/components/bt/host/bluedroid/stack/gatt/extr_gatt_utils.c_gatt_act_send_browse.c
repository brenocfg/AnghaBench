#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tGATT_TCB ;
struct TYPE_4__ {int /*<<< orphan*/  uuid; void* e_handle; void* s_handle; } ;
struct TYPE_5__ {TYPE_1__ browse; } ;
typedef  TYPE_2__ tGATT_CL_MSG ;
typedef  int /*<<< orphan*/  tBT_UUID ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  void* UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  attp_send_cl_msg (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

UINT8 gatt_act_send_browse(tGATT_TCB *p_tcb, UINT16 index, UINT8 op, UINT16 s_handle,
                           UINT16 e_handle, tBT_UUID uuid)
{
    tGATT_CL_MSG     msg;

    msg.browse.s_handle = s_handle;
    msg.browse.e_handle   = e_handle;
    memcpy(&msg.browse.uuid, &uuid, sizeof(tBT_UUID));

    /* write by handle */
    return attp_send_cl_msg(p_tcb, index, op, &msg);
}