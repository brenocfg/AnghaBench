#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* event; } ;
struct TYPE_8__ {void* status; TYPE_2__ hdr; } ;
typedef  TYPE_3__ tBTA_HF_CLIENT_DISC_RESULT ;
typedef  void* UINT16 ;
struct TYPE_6__ {scalar_t__ role; } ;
struct TYPE_9__ {TYPE_1__ scb; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,void*) ; 
 scalar_t__ BTA_HF_CLIENT_ACP ; 
 void* BTA_HF_CLIENT_DISC_ACP_RES_EVT ; 
 void* BTA_HF_CLIENT_DISC_INT_RES_EVT ; 
 TYPE_5__ bta_hf_client_cb ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_3__*) ; 
 scalar_t__ osi_malloc (int) ; 

__attribute__((used)) static void bta_hf_client_sdp_cback(UINT16 status)
{
    tBTA_HF_CLIENT_DISC_RESULT *p_buf;
    UINT16                     event;

    APPL_TRACE_DEBUG("bta_hf_client_sdp_cback status:0x%x", status);

    /* set event according to int/acp */
    if (bta_hf_client_cb.scb.role == BTA_HF_CLIENT_ACP) {
        event = BTA_HF_CLIENT_DISC_ACP_RES_EVT;
    } else {
        event = BTA_HF_CLIENT_DISC_INT_RES_EVT;
    }

    if ((p_buf = (tBTA_HF_CLIENT_DISC_RESULT *) osi_malloc(sizeof(tBTA_HF_CLIENT_DISC_RESULT))) != NULL) {
        p_buf->hdr.event = event;
        p_buf->status = status;
        bta_sys_sendmsg(p_buf);
    }
}