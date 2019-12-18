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
struct TYPE_6__ {scalar_t__ record_handle; scalar_t__ num_attributes; int free_pad_ptr; int /*<<< orphan*/ * attr_pad; TYPE_3__* attribute; } ;
typedef  TYPE_2__ tSDP_RECORD ;
struct TYPE_7__ {scalar_t__ id; scalar_t__ len; int /*<<< orphan*/ * value_ptr; } ;
typedef  TYPE_3__ tSDP_ATTRIBUTE ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT32 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_5__ {scalar_t__ num_records; TYPE_2__* record; } ;
struct TYPE_8__ {TYPE_1__ server_db; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SDP_TRACE_API (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_4__ sdp_cb ; 

BOOLEAN SDP_DeleteAttribute (UINT32 handle, UINT16 attr_id)
{
#if SDP_SERVER_ENABLED == TRUE
    UINT16          xx, yy;
    tSDP_RECORD     *p_rec = &sdp_cb.server_db.record[0];
    UINT8           *pad_ptr;
    UINT32  len;                        /* Number of bytes in the entry */

    /* Find the record in the database */
    for (xx = 0; xx < sdp_cb.server_db.num_records; xx++, p_rec++) {
        if (p_rec->record_handle == handle) {
            tSDP_ATTRIBUTE  *p_attr = &p_rec->attribute[0];

            SDP_TRACE_API("Deleting attr_id 0x%04x for handle 0x%x\n", attr_id, handle);
            /* Found it. Now, find the attribute */
            for (xx = 0; xx < p_rec->num_attributes; xx++, p_attr++) {
                if (p_attr->id == attr_id) {
                    pad_ptr = p_attr->value_ptr;
                    len = p_attr->len;

                    if (len) {
                        for (yy = 0; yy < p_rec->num_attributes; yy++) {
                            if ( p_rec->attribute[yy].value_ptr > pad_ptr ) {
                                p_rec->attribute[yy].value_ptr -= len;
                            }
                        }
                    }

                    /* Found it. Shift everything up one */
                    p_rec->num_attributes--;

                    for (yy = xx; yy < p_rec->num_attributes; yy++, p_attr++) {
                        *p_attr = *(p_attr + 1);
                    }

                    /* adjust attribute values if needed */
                    if (len) {
                        xx = (p_rec->free_pad_ptr - ((pad_ptr + len) -
                                                     &p_rec->attr_pad[0]));
                        for ( yy = 0; yy < xx; yy++, pad_ptr++) {
                            *pad_ptr = *(pad_ptr + len);
                        }
                        p_rec->free_pad_ptr -= len;
                    }
                    return (TRUE);
                }
            }
        }
    }
#endif
    /* If here, not found */
    return (FALSE);
}