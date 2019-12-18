#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  min_16_digit; scalar_t__* bd_name; int /*<<< orphan*/  dev_class; int /*<<< orphan*/  bd_addr; } ;
struct TYPE_6__ {TYPE_1__ pin_req; } ;
typedef  TYPE_2__ tBTA_DM_SEC ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_7__ {int /*<<< orphan*/  (* p_sec_cback ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;
typedef  int /*<<< orphan*/  DEV_CLASS ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  scalar_t__ BD_NAME ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_STRNCPY_S (char*,int,char*,int) ; 
 int BD_NAME_LEN ; 
 int /*<<< orphan*/  BTA_COPY_DEVICE_CLASS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_DM_PIN_REQ_EVT ; 
 int /*<<< orphan*/  BTM_CMD_STARTED ; 
 int /*<<< orphan*/  BTM_NOT_AUTHORIZED ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ bta_dm_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static UINT8 bta_dm_pin_cback (BD_ADDR bd_addr, DEV_CLASS dev_class, BD_NAME bd_name,
                               BOOLEAN min_16_digit)
{
    tBTA_DM_SEC sec_event;

    if (!bta_dm_cb.p_sec_cback) {
        return BTM_NOT_AUTHORIZED;
    }

    bdcpy(sec_event.pin_req.bd_addr, bd_addr);
    BTA_COPY_DEVICE_CLASS(sec_event.pin_req.dev_class, dev_class);
    BCM_STRNCPY_S((char *)sec_event.pin_req.bd_name, sizeof(BD_NAME), (char *)bd_name, (BD_NAME_LEN - 1));
    sec_event.pin_req.bd_name[BD_NAME_LEN - 1] = 0;
    sec_event.pin_req.min_16_digit = min_16_digit;

    bta_dm_cb.p_sec_cback(BTA_DM_PIN_REQ_EVT, &sec_event);
    return BTM_CMD_STARTED;
}