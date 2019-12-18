#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ record_handle; } ;
typedef  TYPE_2__ tSDP_RECORD ;
typedef  scalar_t__ UINT32 ;
struct TYPE_5__ {size_t num_records; TYPE_2__* record; } ;
struct TYPE_7__ {TYPE_1__ server_db; } ;

/* Variables and functions */
 TYPE_4__ sdp_cb ; 

tSDP_RECORD *sdp_db_find_record (UINT32 handle)
{
    tSDP_RECORD     *p_rec;
    tSDP_RECORD     *p_end = &sdp_cb.server_db.record[sdp_cb.server_db.num_records];

    /* Look through the records for the caller's handle */
    for (p_rec = &sdp_cb.server_db.record[0]; p_rec < p_end; p_rec++) {
        if (p_rec->record_handle == handle) {
            return (p_rec);
        }
    }

    /* Record with that handle not found. */
    return (NULL);
}