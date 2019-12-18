#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * p_srvc_cache; } ;
typedef  TYPE_2__ tBTA_GATTC_SERV ;
struct TYPE_6__ {int /*<<< orphan*/  remote_bda; } ;
struct TYPE_8__ {TYPE_1__ api_conn; } ;
typedef  TYPE_3__ tBTA_GATTC_DATA ;
typedef  int /*<<< orphan*/  tBTA_GATTC_CB ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 TYPE_2__* bta_gattc_find_srvr_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ *) ; 

void bta_gattc_process_api_cache_clean(tBTA_GATTC_CB *p_cb, tBTA_GATTC_DATA *p_msg)
{
    tBTA_GATTC_SERV *p_srvc_cb = bta_gattc_find_srvr_cache(p_msg->api_conn.remote_bda);
    UNUSED(p_cb);

    if (p_srvc_cb != NULL && p_srvc_cb->p_srvc_cache != NULL) {
        //mark it and delete the cache */
        list_free(p_srvc_cb->p_srvc_cache);
        p_srvc_cb->p_srvc_cache = NULL;
    }
}