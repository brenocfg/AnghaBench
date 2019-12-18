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
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  int /*<<< orphan*/  tBTM_ESCO_DATA ;
typedef  size_t UINT8 ;
typedef  size_t UINT16 ;
struct TYPE_6__ {TYPE_3__* sco_db; } ;
struct TYPE_8__ {TYPE_2__ sco_cb; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
struct TYPE_7__ {scalar_t__ state; TYPE_1__ esco; } ;

/* Variables and functions */
 size_t BTM_FIRST_ACTIVE_SCO_INDEX ; 
 size_t BTM_MAX_SCO_LINKS ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_TRACE_API (char*,...) ; 
 int /*<<< orphan*/  BTM_WRONG_MODE ; 
 scalar_t__ SCO_ST_CONNECTED ; 
 TYPE_4__ btm_cb ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

tBTM_STATUS BTM_ReadEScoLinkParms (UINT16 sco_inx, tBTM_ESCO_DATA *p_parms)
{
#if (BTM_MAX_SCO_LINKS>0)
    UINT8 index;

    BTM_TRACE_API("BTM_ReadEScoLinkParms -> sco_inx 0x%04x", sco_inx);

    if (sco_inx < BTM_MAX_SCO_LINKS &&
            btm_cb.sco_cb.sco_db[sco_inx].state >= SCO_ST_CONNECTED) {
        *p_parms = btm_cb.sco_cb.sco_db[sco_inx].esco.data;
        return (BTM_SUCCESS);
    }

    if (sco_inx == BTM_FIRST_ACTIVE_SCO_INDEX) {
        for (index = 0; index < BTM_MAX_SCO_LINKS; index++) {
            if (btm_cb.sco_cb.sco_db[index].state >= SCO_ST_CONNECTED) {
                BTM_TRACE_API("BTM_ReadEScoLinkParms the first active SCO index is %d", index);
                *p_parms = btm_cb.sco_cb.sco_db[index].esco.data;
                return (BTM_SUCCESS);
            }
        }
    }

#endif

    BTM_TRACE_API("BTM_ReadEScoLinkParms cannot find the SCO index!");
    memset(p_parms, 0, sizeof(tBTM_ESCO_DATA));
    return (BTM_WRONG_MODE);
}