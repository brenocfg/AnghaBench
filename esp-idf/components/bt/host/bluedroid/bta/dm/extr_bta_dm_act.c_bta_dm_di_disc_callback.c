#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  layer_specific; int /*<<< orphan*/  event; } ;
struct TYPE_5__ {TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_MSG ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_API_DI_DISCOVER_EVT ; 
 int /*<<< orphan*/  BTA_DM_SEARCH_CMPL_EVT ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 scalar_t__ osi_malloc (int) ; 

__attribute__((used)) static void bta_dm_di_disc_callback(UINT16 result)
{
    tBTA_DM_MSG *p_msg;

    if ((p_msg = (tBTA_DM_MSG *) osi_malloc(sizeof(tBTA_DM_MSG))) != NULL) {
        p_msg->hdr.event            = BTA_DM_SEARCH_CMPL_EVT;
        p_msg->hdr.layer_specific   = BTA_DM_API_DI_DISCOVER_EVT;
        p_msg->hdr.offset           = result;
        bta_sys_sendmsg(p_msg);
    }
}