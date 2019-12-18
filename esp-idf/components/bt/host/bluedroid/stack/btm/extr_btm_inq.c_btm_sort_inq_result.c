#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ rssi; } ;
struct TYPE_13__ {TYPE_3__ results; } ;
struct TYPE_14__ {TYPE_4__ inq_info; } ;
typedef  TYPE_5__ tINQ_DB_ENT ;
typedef  int UINT8 ;
struct TYPE_10__ {scalar_t__ num_resp; } ;
struct TYPE_11__ {TYPE_1__ inq_cmpl_info; TYPE_5__* inq_db; } ;
struct TYPE_15__ {TYPE_2__ btm_inq_vars; } ;

/* Variables and functions */
 scalar_t__ BTM_INQ_DB_SIZE ; 
 TYPE_9__ btm_cb ; 
 int /*<<< orphan*/  memcpy (TYPE_5__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  osi_free (TYPE_5__*) ; 
 scalar_t__ osi_malloc (int) ; 

void btm_sort_inq_result(void)
{
    UINT8               xx, yy, num_resp;
    tINQ_DB_ENT         *p_tmp  = NULL;
    tINQ_DB_ENT         *p_ent  = btm_cb.btm_inq_vars.inq_db;
    tINQ_DB_ENT         *p_next = btm_cb.btm_inq_vars.inq_db + 1;
    int                 size;

    num_resp = (btm_cb.btm_inq_vars.inq_cmpl_info.num_resp < BTM_INQ_DB_SIZE) ?
               btm_cb.btm_inq_vars.inq_cmpl_info.num_resp : BTM_INQ_DB_SIZE;

    if ((p_tmp = (tINQ_DB_ENT *)osi_malloc(sizeof(tINQ_DB_ENT))) != NULL) {
        size = sizeof(tINQ_DB_ENT);
        for (xx = 0; xx < num_resp - 1; xx++, p_ent++) {
            for (yy = xx + 1, p_next = p_ent + 1; yy < num_resp; yy++, p_next++) {
                if (p_ent->inq_info.results.rssi < p_next->inq_info.results.rssi) {
                    memcpy (p_tmp,  p_next, size);
                    memcpy (p_next, p_ent,  size);
                    memcpy (p_ent,  p_tmp,  size);
                }
            }
        }

        osi_free(p_tmp);
    }
}