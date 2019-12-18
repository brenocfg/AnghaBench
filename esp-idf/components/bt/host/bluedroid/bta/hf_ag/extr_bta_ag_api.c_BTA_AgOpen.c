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
typedef  int /*<<< orphan*/  tBTA_SERVICE_MASK ;
typedef  int /*<<< orphan*/  tBTA_SEC ;
struct TYPE_4__ {int /*<<< orphan*/  layer_specific; int /*<<< orphan*/  event; } ;
struct TYPE_5__ {int /*<<< orphan*/  sec_mask; int /*<<< orphan*/  services; int /*<<< orphan*/  bd_addr; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_AG_API_OPEN ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_AG_API_OPEN_EVT ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 scalar_t__ osi_malloc (int) ; 

void BTA_AgOpen(UINT16 handle, BD_ADDR bd_addr, tBTA_SEC sec_mask, tBTA_SERVICE_MASK services)
{
    tBTA_AG_API_OPEN  *p_buf;

    if ((p_buf = (tBTA_AG_API_OPEN *) osi_malloc(sizeof(tBTA_AG_API_OPEN))) != NULL) {
        p_buf->hdr.event = BTA_AG_API_OPEN_EVT;
        p_buf->hdr.layer_specific = handle;
        bdcpy(p_buf->bd_addr, bd_addr);
        p_buf->services = services;
        p_buf->sec_mask = sec_mask;
        bta_sys_sendmsg(p_buf);
    }
}