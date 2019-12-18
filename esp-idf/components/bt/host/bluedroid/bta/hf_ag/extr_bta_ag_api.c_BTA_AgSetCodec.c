#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_AG_PEER_CODEC ;
struct TYPE_4__ {int /*<<< orphan*/  layer_specific; int /*<<< orphan*/  event; } ;
struct TYPE_5__ {int /*<<< orphan*/  codec; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_AG_API_SETCODEC ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_AG_API_SETCODEC_EVT ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 scalar_t__ osi_malloc (int) ; 

void BTA_AgSetCodec(UINT16 handle, tBTA_AG_PEER_CODEC codec)
{
    tBTA_AG_API_SETCODEC    *p_buf;

    if ((p_buf = (tBTA_AG_API_SETCODEC *) osi_malloc(sizeof(tBTA_AG_API_SETCODEC))) != NULL) {
        p_buf->hdr.event = BTA_AG_API_SETCODEC_EVT;
        p_buf->hdr.layer_specific = handle;
        p_buf->codec = codec;
        bta_sys_sendmsg(p_buf);
    }
}