#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_3__ {int /*<<< orphan*/  layer_specific; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_HF_CLIENT_API_CLOSE_EVT ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_1__*) ; 
 scalar_t__ osi_malloc (int) ; 

void BTA_HfClientClose(UINT16 handle)
{
    BT_HDR  *p_buf;

    if ((p_buf = (BT_HDR *) osi_malloc(sizeof(BT_HDR))) != NULL) {
        p_buf->event = BTA_HF_CLIENT_API_CLOSE_EVT;
        p_buf->layer_specific = handle;
        bta_sys_sendmsg(p_buf);
    }
}