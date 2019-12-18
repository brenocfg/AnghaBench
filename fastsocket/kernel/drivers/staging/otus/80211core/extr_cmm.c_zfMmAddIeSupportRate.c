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
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  scalar_t__ u8_t ;
typedef  int u16_t ;
struct TYPE_2__ {int bRate; int bRateBasic; int gRate; int gRateBasic; } ;

/* Variables and functions */
 scalar_t__ ZM_RATE_SET_CCK ; 
 scalar_t__ ZM_RATE_SET_OFDM ; 
 TYPE_1__* wd ; 
 scalar_t__* zg11bRateTbl ; 
 scalar_t__* zg11gRateTbl ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_tx_buf_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,scalar_t__) ; 

u16_t zfMmAddIeSupportRate(zdev_t* dev, zbuf_t* buf, u16_t offset, u8_t eid, u8_t rateSet)
{
    u8_t len = 0;
    u16_t i;

    zmw_get_wlan_dev(dev);

    //if ( (rateSet == ZM_RATE_SET_OFDM)&&((wd->gRate & 0xff) == 0) )
    //{
    //    return offset;
    //}

    /* Information : Support Rate */
    if ( rateSet == ZM_RATE_SET_CCK )
    {
        for (i=0; i<4; i++)
        {
            if ((wd->bRate & (0x1<<i)) == (0x1<<i))
            //if ((0xf & (0x1<<i)) == (0x1<<i))
            {
                zmw_tx_buf_writeb(dev, buf, offset+len+2,
                                     zg11bRateTbl[i]+((wd->bRateBasic & (0x1<<i))<<(7-i)));
                len++;
            }
        }
    }
    else if ( rateSet == ZM_RATE_SET_OFDM )
    {
        for (i=0; i<8; i++)
        {
            if ((wd->gRate & (0x1<<i)) == (0x1<<i))
            //if ((0xff & (0x1<<i)) == (0x1<<i))
            {
                zmw_tx_buf_writeb(dev, buf, offset+len+2,
                                     zg11gRateTbl[i]+((wd->gRateBasic & (0x1<<i))<<(7-i)));
                len++;
            }
        }
    }

    if (len > 0)
    {
        /* Element ID */
        zmw_tx_buf_writeb(dev, buf, offset, eid);

        /* Element Length */
        zmw_tx_buf_writeb(dev, buf, offset+1, len);

        /* Return value */
        offset += (2+len);
    }

    return offset;
}