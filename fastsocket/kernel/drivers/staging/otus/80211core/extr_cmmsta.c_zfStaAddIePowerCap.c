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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  scalar_t__ u8_t ;
typedef  int /*<<< orphan*/  u16_t ;

/* Variables and functions */
 int ZM_WLAN_EID_POWER_CAPABILITY ; 
 int zfHpGetMaxTxPower (int /*<<< orphan*/ *) ; 
 int zfHpGetMinTxPower (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_tx_buf_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zmw_tx_buf_writeh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

u16_t zfStaAddIePowerCap(zdev_t* dev, zbuf_t* buf, u16_t offset)
{
    u8_t MaxTxPower;
    u8_t MinTxPower;

    zmw_get_wlan_dev(dev);

    /* Element ID */
    zmw_tx_buf_writeb(dev, buf, offset++, ZM_WLAN_EID_POWER_CAPABILITY);

    /* Element Length */
    zmw_tx_buf_writeb(dev, buf, offset++, 2);

    MinTxPower = (u8_t)(zfHpGetMinTxPower(dev)/2);
    MaxTxPower = (u8_t)(zfHpGetMaxTxPower(dev)/2);

    /* Min Transmit Power Cap */
    zmw_tx_buf_writeh(dev, buf, offset++, MinTxPower);

    /* Max Transmit Power Cap */
    zmw_tx_buf_writeh(dev, buf, offset++, MaxTxPower);

    return offset;
}