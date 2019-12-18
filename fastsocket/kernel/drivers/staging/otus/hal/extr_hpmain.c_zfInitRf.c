#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int u32_t ;
typedef  scalar_t__ u16_t ;
struct zsHpPriv {scalar_t__ hwFrequency; } ;
struct TYPE_2__ {scalar_t__ hpPrivate; } ;

/* Variables and functions */
 int ZM_CMD_RF_INIT ; 
 int /*<<< orphan*/  ZM_OID_INTERNAL_WRITE ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zfGetHwTurnOffdynParam (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*,int*) ; 
 scalar_t__ zfIssueCmd (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfSetBank4AndPowerTable (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfSetRfRegs (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfwSleep (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zm_debug_msg1 (char*,int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfInitRf(zdev_t* dev, u32_t frequency)
{
    u32_t cmd[8];
    u16_t ret;
    int delta_slope_coeff_exp;
    int delta_slope_coeff_man;
    int delta_slope_coeff_exp_shgi;
    int delta_slope_coeff_man_shgi;

    zmw_get_wlan_dev(dev);

    zm_debug_msg1(" initRf frequency = ", frequency);

    if (frequency == 0)
    {
        frequency = 2412;
    }

    /* Bank 0 1 2 3 5 6 7 */
    zfSetRfRegs(dev, frequency);
    /* Bank 4 */
    zfSetBank4AndPowerTable(dev, frequency, 0, 0);

    /* stroe frequency */
    ((struct zsHpPriv*)wd->hpPrivate)->hwFrequency = (u16_t)frequency;

    zfGetHwTurnOffdynParam(dev,
                           frequency, 0, 0,
                           &delta_slope_coeff_exp,
                           &delta_slope_coeff_man,
                           &delta_slope_coeff_exp_shgi,
                           &delta_slope_coeff_man_shgi);

    /* related functions */
    frequency = frequency*1000;
    cmd[0] = 28 | (ZM_CMD_RF_INIT << 8);
    cmd[1] = frequency;
    cmd[2] = 0;//((struct zsHpPriv*)wd->hpPrivate)->hw_DYNAMIC_HT2040_EN;
    cmd[3] = 1;//((wd->ExtOffset << 2) | ((struct zsHpPriv*)wd->hpPrivate)->hw_HT_ENABLE);
    cmd[4] = delta_slope_coeff_exp;
    cmd[5] = delta_slope_coeff_man;
    cmd[6] = delta_slope_coeff_exp_shgi;
    cmd[7] = delta_slope_coeff_man_shgi;

    ret = zfIssueCmd(dev, cmd, 32, ZM_OID_INTERNAL_WRITE, 0);

    // delay temporarily, wait for new PHY and RF
    zfwSleep(dev, 1000);
}