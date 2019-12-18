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
typedef  scalar_t__ tBTM_SCO_DATA_FLAG ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,scalar_t__) ; 
 scalar_t__ BTM_SCO_DATA_CORRECT ; 
 int /*<<< orphan*/  bta_ag_sco_co_in_data (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void bta_ag_sco_read_cback(UINT16 sco_inx, BT_HDR *p_data, tBTM_SCO_DATA_FLAG status)
{
    if (status != BTM_SCO_DATA_CORRECT)
    {
        APPL_TRACE_DEBUG("bta_ag_sco_read_cback: status(%d)", status);
    }

    /* Callout function must free the data. */
    bta_ag_sco_co_in_data(p_data, status);
}