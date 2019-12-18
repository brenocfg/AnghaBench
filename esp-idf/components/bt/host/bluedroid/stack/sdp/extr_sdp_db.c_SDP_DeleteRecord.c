#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ record_handle; scalar_t__ num_attributes; TYPE_1__* attribute; } ;
typedef  TYPE_3__ tSDP_RECORD ;
typedef  scalar_t__ UINT32 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_6__ {scalar_t__ num_records; scalar_t__ di_primary_handle; TYPE_3__* record; } ;
struct TYPE_8__ {TYPE_2__ server_db; } ;
struct TYPE_5__ {int value_ptr; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SDP_TRACE_DEBUG (char*,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_4__ sdp_cb ; 

BOOLEAN SDP_DeleteRecord (UINT32 handle)
{
#if SDP_SERVER_ENABLED == TRUE
    UINT16          xx, yy, zz;
    tSDP_RECORD     *p_rec = &sdp_cb.server_db.record[0];

    if (handle == 0 || sdp_cb.server_db.num_records == 0) {
        /* Delete all records in the database */
        sdp_cb.server_db.num_records = 0;

        /* require new DI record to be created in SDP_SetLocalDiRecord */
        sdp_cb.server_db.di_primary_handle = 0;

        return (TRUE);
    } else {
        /* Find the record in the database */
        for (xx = 0; xx < sdp_cb.server_db.num_records; xx++, p_rec++) {
            if (p_rec->record_handle == handle) {
                /* Found it. Shift everything up one */
                for (yy = xx; yy < sdp_cb.server_db.num_records; yy++, p_rec++) {
                    *p_rec = *(p_rec + 1);

                    /* Adjust the attribute value pointer for each attribute */
                    for (zz = 0; zz < p_rec->num_attributes; zz++) {
                        p_rec->attribute[zz].value_ptr -= sizeof(tSDP_RECORD);
                    }
                }

                sdp_cb.server_db.num_records--;

                SDP_TRACE_DEBUG("SDP_DeleteRecord ok, num_records:%d\n", sdp_cb.server_db.num_records);
                /* if we're deleting the primary DI record, clear the */
                /* value in the control block */
                if ( sdp_cb.server_db.di_primary_handle == handle ) {
                    sdp_cb.server_db.di_primary_handle = 0;
                }

                return (TRUE);
            }
        }
    }
#endif
    return (FALSE);
}