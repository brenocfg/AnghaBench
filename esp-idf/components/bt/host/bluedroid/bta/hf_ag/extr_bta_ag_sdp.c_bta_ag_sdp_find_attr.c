#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__* params; } ;
typedef  TYPE_3__ tSDP_PROTOCOL_ELEM ;
typedef  int /*<<< orphan*/  tSDP_DISC_REC ;
struct TYPE_9__ {scalar_t__ u8; int /*<<< orphan*/  u16; } ;
struct TYPE_10__ {TYPE_1__ v; } ;
struct TYPE_12__ {TYPE_2__ attr_value; } ;
typedef  TYPE_4__ tSDP_DISC_ATTR ;
typedef  int tBTA_SERVICE_MASK ;
struct TYPE_13__ {int peer_version; scalar_t__ role; int /*<<< orphan*/  peer_features; scalar_t__ peer_scn; int /*<<< orphan*/  p_disc_db; } ;
typedef  TYPE_5__ tBTA_AG_SCB ;
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT16 ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_ID_REMOTE_AUDIO_VOLUME_CONTROL ; 
 int /*<<< orphan*/  ATTR_ID_SUPPORTED_FEATURES ; 
 scalar_t__ BTA_AG_INT ; 
 int /*<<< orphan*/  BTA_AG_PEER_FEAT_VOL ; 
 int BTA_HFP_SERVICE_MASK ; 
 int BTA_HSP_SERVICE_MASK ; 
 scalar_t__ FALSE ; 
 int HFP_VERSION_1_1 ; 
 TYPE_4__* SDP_FindAttributeInRec (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDP_FindProfileVersionInRec (int /*<<< orphan*/ *,scalar_t__,int*) ; 
 scalar_t__ SDP_FindProtocolListElemInRec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/ * SDP_FindServiceInDb (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UUID_PROTOCOL_RFCOMM ; 
 scalar_t__ UUID_SERVCLASS_HEADSET ; 
 scalar_t__ UUID_SERVCLASS_HEADSET_HS ; 
 scalar_t__ UUID_SERVCLASS_HF_HANDSFREE ; 

BOOLEAN bta_ag_sdp_find_attr(tBTA_AG_SCB *p_scb, tBTA_SERVICE_MASK service)
{
    tSDP_DISC_REC       *p_rec = NULL;
    tSDP_DISC_ATTR      *p_attr;
    tSDP_PROTOCOL_ELEM  pe;
    UINT16              uuid;
    BOOLEAN             result = FALSE;

    if (service & BTA_HFP_SERVICE_MASK) {
        uuid = UUID_SERVCLASS_HF_HANDSFREE;
        p_scb->peer_version = HFP_VERSION_1_1;   /* Default version */
    } else if (service & BTA_HSP_SERVICE_MASK && p_scb->role == BTA_AG_INT) {
        uuid = UUID_SERVCLASS_HEADSET_HS;
        p_scb->peer_version = 0x0100;   /* Default version */
    } else {
        return result;
    }

    /* loop through all records we found */
    while (TRUE)
    {
        /* get next record; if none found, we're done */
        if ((p_rec = SDP_FindServiceInDb(p_scb->p_disc_db, uuid, p_rec)) == NULL) {
            if (uuid == UUID_SERVCLASS_HEADSET_HS) {
                /* Search again in case the peer device is HSP v1.0 */
                uuid = UUID_SERVCLASS_HEADSET;
                if ((p_rec = SDP_FindServiceInDb(p_scb->p_disc_db, uuid, p_rec)) == NULL) {
                    break;
                }
            } else {
                break;
            }
        }

        /* get scn from proto desc list if initiator */
        if (p_scb->role == BTA_AG_INT) {
            if (SDP_FindProtocolListElemInRec(p_rec, UUID_PROTOCOL_RFCOMM, &pe)) {
                p_scb->peer_scn = (UINT8) pe.params[0];
            } else {
                continue;
            }
        }
        /* get profile version (if failure, version parameter is not updated) */
        SDP_FindProfileVersionInRec(p_rec, uuid, &p_scb->peer_version);
        /* get features if HFP */
        if (service & BTA_HFP_SERVICE_MASK) {
            if ((p_attr = SDP_FindAttributeInRec(p_rec, ATTR_ID_SUPPORTED_FEATURES)) != NULL) {
                /* Found attribute. Get value. */
                /* There might be race condition between SDP and BRSF.  */
                /* Do not update if we already received BRSF.           */
                if (p_scb->peer_features == 0)
                    p_scb->peer_features = p_attr->attr_value.v.u16;
            }
        } else {
            /* HSP */
            if ((p_attr = SDP_FindAttributeInRec(p_rec, ATTR_ID_REMOTE_AUDIO_VOLUME_CONTROL)) != NULL) {
                /* Remote volume control of HSP */
                if (p_attr->attr_value.v.u8) {
                    p_scb->peer_features |= BTA_AG_PEER_FEAT_VOL;
                } else {
                    p_scb->peer_features &= ~BTA_AG_PEER_FEAT_VOL;
                }
            }
        }
        /* found what we needed */
        result = TRUE;
        break;
    }
    return result;
}