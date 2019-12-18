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
struct TYPE_9__ {void* uuid16; } ;
struct TYPE_10__ {void* len; TYPE_1__ uu; } ;
typedef  TYPE_2__ tSDP_UUID ;
typedef  int /*<<< orphan*/  tSDP_DISCOVERY_DB ;
typedef  int tBTA_SERVICE_MASK ;
struct TYPE_11__ {scalar_t__ role; scalar_t__ hsp_version; int /*<<< orphan*/ * p_disc_db; int /*<<< orphan*/  peer_addr; } ;
typedef  TYPE_3__ tBTA_AG_SCB ;
typedef  int UINT8 ;
typedef  int UINT16 ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int ATTR_ID_BT_PROFILE_DESC_LIST ; 
 int ATTR_ID_PROTOCOL_DESC_LIST ; 
 int ATTR_ID_REMOTE_AUDIO_VOLUME_CONTROL ; 
 int ATTR_ID_SERVICE_CLASS_ID_LIST ; 
 int ATTR_ID_SUPPORTED_FEATURES ; 
 scalar_t__ BTA_AG_ACP ; 
 int /*<<< orphan*/  BTA_AG_DISC_BUF_SIZE ; 
 int /*<<< orphan*/  BTA_AG_DISC_FAIL_EVT ; 
 scalar_t__ BTA_AG_INT ; 
 int BTA_HFP_SERVICE_MASK ; 
 int BTA_HSP_SERVICE_MASK ; 
 scalar_t__ FALSE ; 
 scalar_t__ HSP_VERSION_1_2 ; 
 void* LEN_UUID_16 ; 
 scalar_t__ SDP_InitDiscoveryDb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_2__*,int,int*) ; 
 scalar_t__ SDP_ServiceSearchAttributeRequest (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* UUID_SERVCLASS_HEADSET ; 
 void* UUID_SERVCLASS_HEADSET_HS ; 
 void* UUID_SERVCLASS_HF_HANDSFREE ; 
 int /*<<< orphan*/  bta_ag_free_db (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int bta_ag_scb_to_idx (TYPE_3__*) ; 
 int /*<<< orphan*/ * bta_ag_sdp_cback_tbl ; 
 int /*<<< orphan*/  bta_ag_sm_execute (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ osi_malloc (int /*<<< orphan*/ ) ; 

void bta_ag_do_disc(tBTA_AG_SCB *p_scb, tBTA_SERVICE_MASK service)
{
    tSDP_UUID       uuid_list[2];
    UINT16          num_uuid = 1;
    UINT16          attr_list[4];
    UINT8           num_attr;
    BOOLEAN         db_inited = FALSE;

    /* HFP initiator; get proto list and features */
    if (service & BTA_HFP_SERVICE_MASK && p_scb->role == BTA_AG_INT) {
        attr_list[0] = ATTR_ID_SERVICE_CLASS_ID_LIST;
        attr_list[1] = ATTR_ID_PROTOCOL_DESC_LIST;
        attr_list[2] = ATTR_ID_BT_PROFILE_DESC_LIST;
        attr_list[3] = ATTR_ID_SUPPORTED_FEATURES;
        num_attr = 4;
        uuid_list[0].uu.uuid16 = UUID_SERVCLASS_HF_HANDSFREE;
    } else if (service & BTA_HFP_SERVICE_MASK && p_scb->role == BTA_AG_ACP) {
        /* HFP acceptor; get features */
        attr_list[0] = ATTR_ID_SERVICE_CLASS_ID_LIST;
        attr_list[1] = ATTR_ID_BT_PROFILE_DESC_LIST;
        attr_list[2] = ATTR_ID_SUPPORTED_FEATURES;
        num_attr = 3;
        uuid_list[0].uu.uuid16 = UUID_SERVCLASS_HF_HANDSFREE;
    } else if (service & BTA_HSP_SERVICE_MASK && p_scb->role == BTA_AG_INT) {
        /* HSP initiator; get proto list */
        attr_list[0] = ATTR_ID_SERVICE_CLASS_ID_LIST;
        attr_list[1] = ATTR_ID_PROTOCOL_DESC_LIST;
        attr_list[2] = ATTR_ID_BT_PROFILE_DESC_LIST;
        attr_list[3] = ATTR_ID_REMOTE_AUDIO_VOLUME_CONTROL;
        num_attr = 4;
        uuid_list[0].uu.uuid16 = UUID_SERVCLASS_HEADSET;        /* Legacy from HSP v1.0 */
        if (p_scb->hsp_version >= HSP_VERSION_1_2) {
            uuid_list[1].uu.uuid16 = UUID_SERVCLASS_HEADSET_HS;
            num_uuid = 2;
        }
    } else {
        /* HSP acceptor; no discovery */
        return;
    }

    /* allocate buffer for sdp database */
    p_scb->p_disc_db = (tSDP_DISCOVERY_DB *) osi_malloc(BTA_AG_DISC_BUF_SIZE);
    if(p_scb->p_disc_db) {
        /* set up service discovery database; attr happens to be attr_list len */
        uuid_list[0].len = LEN_UUID_16;
        uuid_list[1].len = LEN_UUID_16;
        db_inited = SDP_InitDiscoveryDb(p_scb->p_disc_db, BTA_AG_DISC_BUF_SIZE, num_uuid,
                            uuid_list, num_attr, attr_list);
    }

    if(db_inited) {
        /*Service discovery not initiated */
        db_inited = SDP_ServiceSearchAttributeRequest(p_scb->peer_addr, p_scb->p_disc_db,
                                      bta_ag_sdp_cback_tbl[bta_ag_scb_to_idx(p_scb) - 1]);
    }
    if(!db_inited) {
        /*free discover db */
        bta_ag_free_db(p_scb, NULL);
        /* sent failed event */
        bta_ag_sm_execute(p_scb, BTA_AG_DISC_FAIL_EVT, NULL);
    }
}