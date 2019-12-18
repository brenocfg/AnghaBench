#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int post_sco; int features; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;
typedef  int /*<<< orphan*/  tBTA_AG_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_AG_END_CALL_RES ; 
 int BTA_AG_FEAT_NOSCO ; 
 int /*<<< orphan*/  BTA_AG_IN_CALL_CONN_RES ; 
 int /*<<< orphan*/  BTA_AG_IN_CALL_RES ; 
 int /*<<< orphan*/  BTA_AG_OUT_CALL_ORIG_RES ; 
#define  BTA_AG_POST_SCO_CALL_CONN 132 
#define  BTA_AG_POST_SCO_CALL_END 131 
#define  BTA_AG_POST_SCO_CALL_END_INCALL 130 
#define  BTA_AG_POST_SCO_CALL_ORIG 129 
#define  BTA_AG_POST_SCO_CLOSE_RFC 128 
 void* BTA_AG_POST_SCO_NONE ; 
 int BTA_AG_POST_SCO_RING ; 
 int /*<<< orphan*/  bta_ag_inband_enabled (TYPE_1__*) ; 
 int /*<<< orphan*/  bta_ag_rfc_do_close (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_ag_sco_open (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_ag_send_call_inds (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_ag_send_ring (TYPE_1__*,int /*<<< orphan*/ *) ; 

void bta_ag_post_sco_close(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data)
{
    switch (p_scb->post_sco) {
        case BTA_AG_POST_SCO_CLOSE_RFC:
            bta_ag_rfc_do_close(p_scb, p_data);
            p_scb->post_sco = BTA_AG_POST_SCO_NONE;
            break;

        case BTA_AG_POST_SCO_CALL_CONN:
            bta_ag_send_call_inds(p_scb, BTA_AG_IN_CALL_CONN_RES);
            p_scb->post_sco = BTA_AG_POST_SCO_NONE;
            break;

        case BTA_AG_POST_SCO_CALL_ORIG:
            bta_ag_send_call_inds(p_scb, BTA_AG_OUT_CALL_ORIG_RES);
            p_scb->post_sco = BTA_AG_POST_SCO_NONE;
            break;

        case BTA_AG_POST_SCO_CALL_END:
            bta_ag_send_call_inds(p_scb, BTA_AG_END_CALL_RES);
            p_scb->post_sco = BTA_AG_POST_SCO_NONE;
            break;

        case BTA_AG_POST_SCO_CALL_END_INCALL:
        {
            bta_ag_send_call_inds(p_scb, BTA_AG_END_CALL_RES);
            /* Sending callsetup IND and Ring were defered to after SCO close. */
            bta_ag_send_call_inds(p_scb, BTA_AG_IN_CALL_RES);

            if (bta_ag_inband_enabled(p_scb) && !(p_scb->features & BTA_AG_FEAT_NOSCO)) {
                p_scb->post_sco = BTA_AG_POST_SCO_RING;
                bta_ag_sco_open(p_scb, p_data);
            } else {
                p_scb->post_sco = BTA_AG_POST_SCO_NONE;
                bta_ag_send_ring(p_scb, p_data);
            }
            break;
        }

        default:
            break;
    }
}