#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int len; int event; TYPE_3__* p_data; } ;
typedef  TYPE_2__ tBTA_DM_SEARCH_PARAM ;
typedef  int /*<<< orphan*/  tBTA_DM_SEARCH ;
typedef  int /*<<< orphan*/  btc_msg_t ;
struct TYPE_9__ {int num_uuids; TYPE_3__* p_raw_data; TYPE_3__* p_uuid_list; int /*<<< orphan*/  result; } ;
struct TYPE_11__ {TYPE_1__ disc_res; } ;
typedef  TYPE_3__ UINT8 ;

/* Variables and functions */
#define  BTA_DM_DISC_RES_EVT 128 
 int /*<<< orphan*/  BTA_SUCCESS ; 
 int MAX_UUID_SIZE ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  osi_free (TYPE_3__*) ; 
 TYPE_3__* osi_malloc (int) ; 

__attribute__((used)) static void search_services_copy_cb(btc_msg_t *msg, void *p_dest, void *p_src)
{
    tBTA_DM_SEARCH_PARAM *p_dest_data =  (tBTA_DM_SEARCH_PARAM *) p_dest;
    tBTA_DM_SEARCH_PARAM *p_src_data =  (tBTA_DM_SEARCH_PARAM *) p_src;

    if (!p_src) {
        return;
    }
    p_dest_data->p_data = osi_malloc(p_dest_data->len);
    memset(p_dest_data->p_data, 0x00, p_dest_data->len);
    memcpy(p_dest_data->p_data, p_src_data->p_data, p_dest_data->len);

    if ( p_dest_data->len > sizeof(tBTA_DM_SEARCH)){
        switch (p_dest_data->event) {
        case BTA_DM_DISC_RES_EVT: {
            if (p_src_data->p_data->disc_res.result == BTA_SUCCESS) {
                if (p_src_data->p_data->disc_res.num_uuids > 0) {
                    p_dest_data->p_data->disc_res.p_uuid_list = (UINT8 *)(p_dest_data->p_data) + sizeof(tBTA_DM_SEARCH);
                    memcpy(p_dest_data->p_data->disc_res.p_uuid_list, p_src_data->p_data->disc_res.p_uuid_list,
                           p_src_data->p_data->disc_res.num_uuids * MAX_UUID_SIZE);
                    osi_free(p_src_data->p_data->disc_res.p_uuid_list);
                    p_src_data->p_data->disc_res.p_uuid_list = NULL;
                }
                if (p_src_data->p_data->disc_res.p_raw_data != NULL) {
                    osi_free(p_src_data->p_data->disc_res.p_raw_data);
                    p_src_data->p_data->disc_res.p_raw_data = NULL;
                }
            }
        } break;
        }
    }
}