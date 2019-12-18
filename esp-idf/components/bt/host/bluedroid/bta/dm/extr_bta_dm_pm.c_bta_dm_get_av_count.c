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
typedef  scalar_t__ UINT8 ;
struct TYPE_4__ {int count; TYPE_1__* conn_srvc; } ;
struct TYPE_3__ {scalar_t__ id; } ;

/* Variables and functions */
 scalar_t__ BTA_ID_AV ; 
 TYPE_2__ bta_dm_conn_srvcs ; 

UINT8 bta_dm_get_av_count(void)
{
    UINT8 count = 0;
    for (int i = 0; i < bta_dm_conn_srvcs.count; i++) {
        if (bta_dm_conn_srvcs.conn_srvc[i].id == BTA_ID_AV) {
            ++count;
        }
    }
    return count;
}