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
typedef  int /*<<< orphan*/  tSDP_DISC_REC ;
typedef  int /*<<< orphan*/  tSDP_DISCOVERY_DB ;
typedef  scalar_t__ UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/ * SDP_FindServiceInDb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UUID_SERVCLASS_PNP_INFORMATION ; 

UINT8 SDP_GetNumDiRecords( tSDP_DISCOVERY_DB *p_db )
{
#if SDP_CLIENT_ENABLED == TRUE
    UINT8   num_records = 0;
    tSDP_DISC_REC *p_curr_record = NULL;

    do {
        p_curr_record = SDP_FindServiceInDb( p_db, UUID_SERVCLASS_PNP_INFORMATION,
                                             p_curr_record );
        if ( p_curr_record ) {
            num_records++;
        }
    } while ( p_curr_record );

    return num_records;
#else
    return 0;
#endif
}