#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  appl_knows_rem_name; } ;
typedef  TYPE_4__ tBTM_INQ_INFO ;
struct TYPE_8__ {int /*<<< orphan*/  bd_addr; scalar_t__* bd_name; } ;
struct TYPE_10__ {TYPE_1__ disc_res; } ;
struct TYPE_9__ {TYPE_3__ result; } ;
struct TYPE_12__ {TYPE_2__ rem_name; } ;
typedef  TYPE_5__ tBTA_DM_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*) ; 
 TYPE_4__* BTM_InqDbRead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bta_dm_discover_device (int /*<<< orphan*/ ) ; 

void bta_dm_disc_rmt_name (tBTA_DM_MSG *p_data)
{
    tBTM_INQ_INFO *p_btm_inq_info;

    APPL_TRACE_DEBUG("bta_dm_disc_rmt_name");

    p_btm_inq_info = BTM_InqDbRead (p_data->rem_name.result.disc_res.bd_addr);
    if ( p_btm_inq_info ) {
        if ( p_data->rem_name.result.disc_res.bd_name[0] ) {
            p_btm_inq_info->appl_knows_rem_name = TRUE;
        }
    }
#if (SDP_INCLUDED == TRUE)
    bta_dm_discover_device(p_data->rem_name.result.disc_res.bd_addr);
#endif  ///SDP_INCLUDED == TRUE
}