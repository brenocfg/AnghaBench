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
struct TYPE_4__ {int /*<<< orphan*/  event; } ;
struct TYPE_5__ {int /*<<< orphan*/  p_pin; int /*<<< orphan*/  pin_len; scalar_t__ accept; int /*<<< orphan*/  bd_addr; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_API_PIN_REPLY ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_API_PIN_REPLY_EVT ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ osi_malloc (int) ; 

void BTA_DmPinReply(BD_ADDR bd_addr, BOOLEAN accept, UINT8 pin_len, UINT8 *p_pin)
{
    tBTA_DM_API_PIN_REPLY    *p_msg;

    if ((p_msg = (tBTA_DM_API_PIN_REPLY *) osi_malloc(sizeof(tBTA_DM_API_PIN_REPLY))) != NULL) {
        p_msg->hdr.event = BTA_DM_API_PIN_REPLY_EVT;
        bdcpy(p_msg->bd_addr, bd_addr);
        p_msg->accept = accept;
        if (accept) {
            p_msg->pin_len = pin_len;
            memcpy(p_msg->p_pin, p_pin, pin_len);
        }
        bta_sys_sendmsg(p_msg);
    }

}