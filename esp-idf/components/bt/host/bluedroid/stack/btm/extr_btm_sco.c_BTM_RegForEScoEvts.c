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
typedef  int /*<<< orphan*/  tBTM_ESCO_CBACK ;
typedef  size_t UINT16 ;
struct TYPE_5__ {TYPE_3__* sco_db; int /*<<< orphan*/  esco_supported; } ;
struct TYPE_8__ {TYPE_1__ sco_cb; } ;
struct TYPE_6__ {int /*<<< orphan*/ * p_esco_cback; } ;
struct TYPE_7__ {scalar_t__ state; TYPE_2__ esco; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_ILLEGAL_VALUE ; 
 size_t BTM_MAX_SCO_LINKS ; 
 int /*<<< orphan*/  BTM_MODE_UNSUPPORTED ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 scalar_t__ SCO_ST_UNUSED ; 
 TYPE_4__ btm_cb ; 

tBTM_STATUS BTM_RegForEScoEvts (UINT16 sco_inx, tBTM_ESCO_CBACK *p_esco_cback)
{
#if (BTM_MAX_SCO_LINKS>0)
    if (!btm_cb.sco_cb.esco_supported) {
        btm_cb.sco_cb.sco_db[sco_inx].esco.p_esco_cback = NULL;
        return (BTM_MODE_UNSUPPORTED);
    }

    if (sco_inx < BTM_MAX_SCO_LINKS &&
            btm_cb.sco_cb.sco_db[sco_inx].state != SCO_ST_UNUSED) {
        btm_cb.sco_cb.sco_db[sco_inx].esco.p_esco_cback = p_esco_cback;
        return (BTM_SUCCESS);
    }
    return (BTM_ILLEGAL_VALUE);
#else
    return (BTM_MODE_UNSUPPORTED);
#endif
}