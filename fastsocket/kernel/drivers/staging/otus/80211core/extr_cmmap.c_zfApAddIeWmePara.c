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
typedef  int /*<<< orphan*/  u16_t ;
struct TYPE_3__ {scalar_t__ uapsdEnabled; } ;
struct TYPE_4__ {TYPE_1__ ap; } ;

/* Variables and functions */
 int ZM_WLAN_EID_WIFI_IE ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_tx_buf_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

u16_t zfApAddIeWmePara(zdev_t* dev, zbuf_t* buf, u16_t offset, u16_t vap)
{
    zmw_get_wlan_dev(dev);

    /* Element ID */
    zmw_tx_buf_writeb(dev, buf, offset++, ZM_WLAN_EID_WIFI_IE);

    /* Element Length */
    zmw_tx_buf_writeb(dev, buf, offset++, 24);

    /* OUI */
    zmw_tx_buf_writeb(dev, buf, offset++, 0x00);
    zmw_tx_buf_writeb(dev, buf, offset++, 0x50);
    zmw_tx_buf_writeb(dev, buf, offset++, 0xF2);
    zmw_tx_buf_writeb(dev, buf, offset++, 0x02);
    zmw_tx_buf_writeb(dev, buf, offset++, 0x01);
    zmw_tx_buf_writeb(dev, buf, offset++, 0x01);

    /* QoS Info */
    if (wd->ap.uapsdEnabled)
    {
        zmw_tx_buf_writeb(dev, buf, offset++, 0x81);
    }
    else
    {
    zmw_tx_buf_writeb(dev, buf, offset++, 0x01);
    }

    /* Reserved */
    zmw_tx_buf_writeb(dev, buf, offset++, 0x00);

    /* Best Effort AC parameters */
    zmw_tx_buf_writeb(dev, buf, offset++, 0x03);
    zmw_tx_buf_writeb(dev, buf, offset++, 0xA4);
    zmw_tx_buf_writeb(dev, buf, offset++, 0x00);
    zmw_tx_buf_writeb(dev, buf, offset++, 0x00);
    /* Backfround AC parameters */
    zmw_tx_buf_writeb(dev, buf, offset++, 0x27);
    zmw_tx_buf_writeb(dev, buf, offset++, 0xA4);
    zmw_tx_buf_writeb(dev, buf, offset++, 0x00);
    zmw_tx_buf_writeb(dev, buf, offset++, 0x00);
    /* Video AC parameters */
    zmw_tx_buf_writeb(dev, buf, offset++, 0x42);
    zmw_tx_buf_writeb(dev, buf, offset++, 0x43);
    zmw_tx_buf_writeb(dev, buf, offset++, 0x5E);
    zmw_tx_buf_writeb(dev, buf, offset++, 0x00);
    /* Voice AC parameters */
    zmw_tx_buf_writeb(dev, buf, offset++, 0x62);
    zmw_tx_buf_writeb(dev, buf, offset++, 0x32);
    zmw_tx_buf_writeb(dev, buf, offset++, 0x2F);
    zmw_tx_buf_writeb(dev, buf, offset++, 0x00);

    return offset;
}