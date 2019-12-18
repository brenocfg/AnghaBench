#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ uuid16; scalar_t__ uuid32; int /*<<< orphan*/  uuid128; } ;
struct TYPE_6__ {int len; TYPE_1__ uu; } ;
typedef  TYPE_2__ tBT_UUID ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

BOOLEAN sdpu_compare_bt_uuids (tBT_UUID *p_uuid1, tBT_UUID *p_uuid2)
{
    /* Lengths must match for BT UUIDs to match */
    if (p_uuid1->len == p_uuid2->len) {
        if (p_uuid1->len == 2) {
            return (p_uuid1->uu.uuid16 == p_uuid2->uu.uuid16);
        } else if (p_uuid1->len == 4) {
            return (p_uuid1->uu.uuid32 == p_uuid2->uu.uuid32);
        } else if (!memcmp (p_uuid1->uu.uuid128, p_uuid2->uu.uuid128, 16)) {
            return (TRUE);
        }
    }

    return (FALSE);
}