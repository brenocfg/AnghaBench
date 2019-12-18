#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int u8_t ;
struct zsTkipSeed {int dummy; } ;
struct TYPE_3__ {scalar_t__ encryMode; scalar_t__ wpaState; struct zsTkipSeed* rxSeed; } ;
struct TYPE_4__ {TYPE_1__ sta; } ;

/* Variables and functions */
 scalar_t__ ZM_AES ; 
 scalar_t__ ZM_STA_WPA_STATE_PK_OK ; 
 scalar_t__ ZM_TKIP ; 
 scalar_t__ ZM_WLAN_HEADER_A1_OFFSET ; 
 scalar_t__ ZM_WLAN_HEADER_IV_OFFSET ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

struct zsTkipSeed* zfStaGetRxSeed(zdev_t* dev, zbuf_t* buf)
{
    u8_t keyIndex;
    u8_t da0;

    zmw_get_wlan_dev(dev);

    /* if need not check MIC, return NULL */
    if ( ((wd->sta.encryMode != ZM_TKIP)&&(wd->sta.encryMode != ZM_AES))||
         (wd->sta.wpaState < ZM_STA_WPA_STATE_PK_OK) )
    {
        return NULL;
    }

    da0 = zmw_rx_buf_readb(dev, buf, ZM_WLAN_HEADER_A1_OFFSET);

    if ((zmw_rx_buf_readb(dev, buf, 0) & 0x80) == 0x80)
        keyIndex = zmw_rx_buf_readb(dev, buf, ZM_WLAN_HEADER_IV_OFFSET+5); /* Qos Packet*/
    else
        keyIndex = zmw_rx_buf_readb(dev, buf, ZM_WLAN_HEADER_IV_OFFSET+3); /* normal Packet*/
    keyIndex = (keyIndex & 0xc0) >> 6;

    return (&wd->sta.rxSeed[keyIndex]);
}