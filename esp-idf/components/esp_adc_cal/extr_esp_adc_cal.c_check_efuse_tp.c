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

/* Variables and functions */
 int /*<<< orphan*/  BLK3_RESERVED_REG ; 
 scalar_t__ CHECK_BLK3_FLAG ; 
 int /*<<< orphan*/  EFUSE_RD_ADC1_TP_HIGH ; 
 int /*<<< orphan*/  EFUSE_RD_ADC1_TP_LOW ; 
 int /*<<< orphan*/  EFUSE_RD_ADC2_TP_HIGH ; 
 int /*<<< orphan*/  EFUSE_RD_ADC2_TP_LOW ; 
 int /*<<< orphan*/  EFUSE_RD_BLK3_PART_RESERVE ; 
 scalar_t__ REG_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TP_REG ; 

__attribute__((used)) static bool check_efuse_tp(void)
{
    //Check if Two Point values are burned in eFuse
    if (CHECK_BLK3_FLAG && (REG_GET_FIELD(BLK3_RESERVED_REG, EFUSE_RD_BLK3_PART_RESERVE) == 0)) {
        return false;
    }
    //All TP cal values must be non zero
    if ((REG_GET_FIELD(TP_REG, EFUSE_RD_ADC1_TP_LOW) != 0) &&
        (REG_GET_FIELD(TP_REG, EFUSE_RD_ADC2_TP_LOW) != 0) &&
        (REG_GET_FIELD(TP_REG, EFUSE_RD_ADC1_TP_HIGH) != 0) &&
        (REG_GET_FIELD(TP_REG, EFUSE_RD_ADC2_TP_HIGH) != 0)) {
        return true;
    } else {
        return false;
    }
}