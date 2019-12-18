#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  uuid16; } ;
struct TYPE_7__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {TYPE_2__ uu; TYPE_1__ member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ tBT_UUID ;
typedef  int /*<<< orphan*/  UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  GATT_DESCR_AGGR_FORMAT ; 
 int /*<<< orphan*/  GATT_DESCR_CLT_CONFIG ; 
 int /*<<< orphan*/  GATT_DESCR_EXT_DSCPTOR ; 
 int /*<<< orphan*/  GATT_DESCR_PRES_FORMAT ; 
 int /*<<< orphan*/  GATT_DESCR_SVR_CONFIG ; 
 int /*<<< orphan*/  GATT_DESCR_UNKNOWN ; 
 int /*<<< orphan*/  GATT_DESCR_USER_DSCPTOR ; 
 int /*<<< orphan*/  GATT_DESCR_VALID_RANGE ; 
 int /*<<< orphan*/  GATT_UUID_CHAR_EXT_PROP ; 
 int /*<<< orphan*/  LEN_UUID_16 ; 
 scalar_t__ gatt_uuid_compare (TYPE_3__,TYPE_3__) ; 

UINT8 gatt_convertchar_descr_type(tBT_UUID *p_descr_uuid)
{
    tBT_UUID std_descr = {LEN_UUID_16, {GATT_UUID_CHAR_EXT_PROP}};

    if (gatt_uuid_compare(std_descr, * p_descr_uuid)) {
        return GATT_DESCR_EXT_DSCPTOR;
    }

    std_descr.uu.uuid16 ++;
    if (gatt_uuid_compare(std_descr,  * p_descr_uuid)) {
        return GATT_DESCR_USER_DSCPTOR;
    }

    std_descr.uu.uuid16 ++;
    if (gatt_uuid_compare(std_descr,  * p_descr_uuid)) {
        return GATT_DESCR_CLT_CONFIG;
    }

    std_descr.uu.uuid16 ++;
    if (gatt_uuid_compare(std_descr,  * p_descr_uuid)) {
        return GATT_DESCR_SVR_CONFIG;
    }

    std_descr.uu.uuid16 ++;
    if (gatt_uuid_compare(std_descr,  * p_descr_uuid)) {
        return GATT_DESCR_PRES_FORMAT;
    }

    std_descr.uu.uuid16 ++;
    if (gatt_uuid_compare(std_descr,  * p_descr_uuid)) {
        return GATT_DESCR_AGGR_FORMAT;
    }

    std_descr.uu.uuid16 ++;
    if (gatt_uuid_compare(std_descr,  * p_descr_uuid)) {
        return GATT_DESCR_VALID_RANGE;
    }


    return GATT_DESCR_UNKNOWN;
}