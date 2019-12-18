#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int u8_t ;
typedef  int u16_t ;
struct TYPE_4__ {int wdsBitmap; int** macAddr; } ;
struct TYPE_5__ {TYPE_1__ wds; } ;
struct TYPE_6__ {TYPE_2__ ap; } ;

/* Variables and functions */
 int ZM_ERR_STA_NOT_ASSOCIATED ; 
 int ZM_MAX_WDS_SUPPORT ; 
 int ZM_STATE_ASOC ; 
 int ZM_SUCCESS ; 
 int /*<<< orphan*/  ZM_WLAN_FRAME_TYPE_DEAUTH ; 
 TYPE_3__* wd ; 
 int zfApGetSTAInfoAndUpdatePs (int /*<<< orphan*/ *,int*,int*,int*,int,int*) ; 
 int /*<<< orphan*/  zfSendMmFrame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int zmw_rx_buf_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zmw_rx_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

u16_t zfApUpdatePsBit(zdev_t* dev, zbuf_t* buf, u8_t* vap, u8_t* uapsdTrig)
{
    u16_t staState;
    u16_t aid;
    u16_t psBit;
    u16_t src[3];
    u16_t dst[1];
    u16_t i;

    zmw_get_wlan_dev(dev);

    src[0] = zmw_rx_buf_readh(dev, buf, 10);
    src[1] = zmw_rx_buf_readh(dev, buf, 12);
    src[2] = zmw_rx_buf_readh(dev, buf, 14);

    if ((zmw_rx_buf_readb(dev, buf, 1) & 0x3) != 3)
    {
        /* AP */
        dst[0] = zmw_rx_buf_readh(dev, buf, 4);

        psBit = (zmw_rx_buf_readb(dev, buf, 1) & 0x10) >> 4;
        /* Get AID and update STA PS mode */
        aid = zfApGetSTAInfoAndUpdatePs(dev, src, &staState, vap, psBit, uapsdTrig);

        /* if STA not associated, send deauth */
        if ((aid == 0xffff) || (staState != ZM_STATE_ASOC))
        {
            if ((dst[0]&0x1)==0)
            {
                zfSendMmFrame(dev, ZM_WLAN_FRAME_TYPE_DEAUTH, src, 0x7,
                        0, 0);
            }

            return ZM_ERR_STA_NOT_ASSOCIATED;
        }
    } /* if ((zmw_rx_buf_readb(dev, buf, 1) & 0x3) != 3) */
    else
    {
        /* WDS */
        for (i=0; i<ZM_MAX_WDS_SUPPORT; i++)
        {
            if ((wd->ap.wds.wdsBitmap & (1<<i)) != 0)
            {
                if ((src[0] == wd->ap.wds.macAddr[i][0])
                        && (src[1] == wd->ap.wds.macAddr[i][1])
                        && (src[2] == wd->ap.wds.macAddr[i][2]))
                {
                    *vap = 0x20 + i;
                    break;
                }
            }
        }
    }
    return ZM_SUCCESS;
}