#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tDIS_ATTR_MASK ;
typedef  int UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  DIS_ATTR_FW_NUM_BIT ; 
 int /*<<< orphan*/  DIS_ATTR_HW_NUM_BIT ; 
 int /*<<< orphan*/  DIS_ATTR_IEEE_DATA_BIT ; 
 int /*<<< orphan*/  DIS_ATTR_MANU_NAME_BIT ; 
 int /*<<< orphan*/  DIS_ATTR_MODEL_NUM_BIT ; 
 int /*<<< orphan*/  DIS_ATTR_PNP_ID_BIT ; 
 int /*<<< orphan*/  DIS_ATTR_SERIAL_NUM_BIT ; 
 int /*<<< orphan*/  DIS_ATTR_SW_NUM_BIT ; 
 int /*<<< orphan*/  DIS_ATTR_SYS_ID_BIT ; 
#define  GATT_UUID_FW_VERSION_STR 136 
#define  GATT_UUID_HW_VERSION_STR 135 
#define  GATT_UUID_IEEE_DATA 134 
#define  GATT_UUID_MANU_NAME 133 
#define  GATT_UUID_MODEL_NUMBER_STR 132 
#define  GATT_UUID_PNP_ID 131 
#define  GATT_UUID_SERIAL_NUMBER_STR 130 
#define  GATT_UUID_SW_VERSION_STR 129 
#define  GATT_UUID_SYSTEM_ID 128 

__attribute__((used)) static tDIS_ATTR_MASK dis_uuid_to_attr(UINT16 uuid)
{
    switch (uuid) {
    case GATT_UUID_SYSTEM_ID:
        return DIS_ATTR_SYS_ID_BIT;
    case GATT_UUID_MODEL_NUMBER_STR:
        return DIS_ATTR_MODEL_NUM_BIT;
    case GATT_UUID_SERIAL_NUMBER_STR:
        return DIS_ATTR_SERIAL_NUM_BIT;
    case GATT_UUID_FW_VERSION_STR:
        return DIS_ATTR_FW_NUM_BIT;
    case GATT_UUID_HW_VERSION_STR:
        return DIS_ATTR_HW_NUM_BIT;
    case GATT_UUID_SW_VERSION_STR:
        return DIS_ATTR_SW_NUM_BIT;
    case GATT_UUID_MANU_NAME:
        return DIS_ATTR_MANU_NAME_BIT;
    case GATT_UUID_IEEE_DATA:
        return DIS_ATTR_IEEE_DATA_BIT;
    case GATT_UUID_PNP_ID:
        return DIS_ATTR_PNP_ID_BIT;
    default:
        return 0;
    };
}