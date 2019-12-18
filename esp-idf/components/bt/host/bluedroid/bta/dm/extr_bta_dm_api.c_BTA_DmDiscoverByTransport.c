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
typedef  int /*<<< orphan*/  tBTA_TRANSPORT ;
typedef  int /*<<< orphan*/  tBTA_SERVICE_MASK_EXT ;
typedef  int /*<<< orphan*/  tBTA_DM_SEARCH_CBACK ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  bta_dm_discover_send_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void BTA_DmDiscoverByTransport(BD_ADDR bd_addr, tBTA_SERVICE_MASK_EXT *p_services,
                               tBTA_DM_SEARCH_CBACK *p_cback, BOOLEAN sdp_search,
                               tBTA_TRANSPORT transport)
{
#if BLE_INCLUDED == TRUE && BTA_GATT_INCLUDED == TRUE && SDP_INCLUDED == TRUE
    bta_dm_discover_send_msg(bd_addr, p_services, p_cback, sdp_search, transport);
#endif
}