#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ transport; } ;
typedef  TYPE_1__ tACL_CONN ;
typedef  size_t UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_4__ {TYPE_1__* acl_db; } ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_API (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ BT_TRANSPORT_LE ; 
 int FALSE ; 
 size_t MAX_L2CAP_LINKS ; 
 TYPE_2__ btm_cb ; 
 size_t btm_handle_to_acl_index (int /*<<< orphan*/ ) ; 

BOOLEAN BTM_IsBleConnection (UINT16 conn_handle)
{
#if (BLE_INCLUDED == TRUE)
    UINT8                xx;
    tACL_CONN            *p;

    BTM_TRACE_API ("BTM_IsBleConnection: conn_handle: %d", conn_handle);

    xx = btm_handle_to_acl_index (conn_handle);
    if (xx >= MAX_L2CAP_LINKS) {
        return FALSE;
    }

    p = &btm_cb.acl_db[xx];

    return (p->transport == BT_TRANSPORT_LE);
#else
    return FALSE;
#endif
}