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
struct TYPE_5__ {int /*<<< orphan*/ * uuid128; int /*<<< orphan*/  uuid32; int /*<<< orphan*/  uuid16; } ;
struct TYPE_6__ {scalar_t__ len; TYPE_1__ uu; } ;
typedef  TYPE_2__ tBT_UUID ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int LEN_UUID_128 ; 
 scalar_t__ LEN_UUID_16 ; 
 scalar_t__ LEN_UUID_32 ; 
 int TRUE ; 
 int /*<<< orphan*/  gatt_convert_uuid16_to_uuid128 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_convert_uuid32_to_uuid128 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

BOOLEAN gatt_uuid_compare (tBT_UUID src, tBT_UUID tar)
{
    UINT8  su[LEN_UUID_128], tu[LEN_UUID_128];
    UINT8  *ps, *pt;

    /* any of the UUID is unspecified */
    if (src.len == 0 || tar.len == 0) {
        return TRUE;
    }

    /* If both are 16-bit, we can do a simple compare */
    if (src.len == LEN_UUID_16 && tar.len == LEN_UUID_16) {
        return src.uu.uuid16 == tar.uu.uuid16;
    }

    /* If both are 32-bit, we can do a simple compare */
    if (src.len == LEN_UUID_32 && tar.len == LEN_UUID_32) {
        return src.uu.uuid32 == tar.uu.uuid32;
    }

    /* One or both of the UUIDs is 128-bit */
    if (src.len == LEN_UUID_16) {
        /* convert a 16 bits UUID to 128 bits value */
        gatt_convert_uuid16_to_uuid128(su, src.uu.uuid16);
        ps = su;
    } else if (src.len == LEN_UUID_32) {
        gatt_convert_uuid32_to_uuid128(su, src.uu.uuid32);
        ps = su;
    } else {
        ps = src.uu.uuid128;
    }

    if (tar.len == LEN_UUID_16) {
        /* convert a 16 bits UUID to 128 bits value */
        gatt_convert_uuid16_to_uuid128(tu, tar.uu.uuid16);
        pt = tu;
    } else if (tar.len == LEN_UUID_32) {
        /* convert a 32 bits UUID to 128 bits value */
        gatt_convert_uuid32_to_uuid128(tu, tar.uu.uuid32);
        pt = tu;
    } else {
        pt = tar.uu.uuid128;
    }

    return (memcmp(ps, pt, LEN_UUID_128) == 0);
}