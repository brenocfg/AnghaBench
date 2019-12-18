#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  inq_info; scalar_t__ in_use; } ;
typedef  TYPE_2__ tINQ_DB_ENT ;
typedef  int /*<<< orphan*/  tBTM_INQ_INFO ;
typedef  scalar_t__ UINT16 ;
struct TYPE_4__ {TYPE_2__* inq_db; } ;
struct TYPE_6__ {TYPE_1__ btm_inq_vars; } ;

/* Variables and functions */
 scalar_t__ BTM_INQ_DB_SIZE ; 
 TYPE_3__ btm_cb ; 

tBTM_INQ_INFO *BTM_InqDbFirst (void)
{
    UINT16       xx;
    tINQ_DB_ENT  *p_ent = btm_cb.btm_inq_vars.inq_db;

    for (xx = 0; xx < BTM_INQ_DB_SIZE; xx++, p_ent++) {
        if (p_ent->in_use) {
            return (&p_ent->inq_info);
        }
    }

    /* If here, no used entry found */
    return ((tBTM_INQ_INFO *)NULL);
}