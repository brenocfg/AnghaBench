#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tSDP_UUID_SEQ ;
typedef  int /*<<< orphan*/  tSDP_RECORD ;
typedef  int /*<<< orphan*/  tSDP_ATTR_SEQ ;
typedef  int UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/ * sdp_db_service_search (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sdpu_get_attrib_seq_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

UINT16 sdpu_get_list_len(tSDP_UUID_SEQ *uid_seq, tSDP_ATTR_SEQ *attr_seq)
{
    tSDP_RECORD    *p_rec;
    UINT16 len = 0;
    UINT16 len1;

    for (p_rec = sdp_db_service_search (NULL, uid_seq); p_rec; p_rec = sdp_db_service_search (p_rec, uid_seq)) {
        len += 3;

        len1 = sdpu_get_attrib_seq_len(p_rec, attr_seq );

        if (len1 != 0) {
            len += len1;
        } else {
            len -= 3;
        }
    }
    return len;
}