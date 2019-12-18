#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  size_t u8_t ;
typedef  int u16_t ;
struct zsAdditionInfo {int dummy; } ;
struct TYPE_6__ {int* encryMode; } ;
struct TYPE_7__ {int* encryMode; TYPE_2__ wds; TYPE_1__* staTable; } ;
struct TYPE_8__ {scalar_t__ wlanMode; TYPE_3__ ap; } ;
struct TYPE_5__ {int encryMode; } ;

/* Variables and functions */
#define  ZM_AES 133 
#define  ZM_CENC 132 
 size_t ZM_MAX_AP_SUPPORT ; 
 int ZM_MAX_WDS_SUPPORT ; 
 scalar_t__ ZM_MODE_AP ; 
 scalar_t__ ZM_MODE_PSEUDO ; 
#define  ZM_TKIP 131 
#define  ZM_WEP128 130 
#define  ZM_WEP256 129 
#define  ZM_WEP64 128 
 scalar_t__ ZM_WLAN_HEADER_A2_OFFSET ; 
 TYPE_4__* wd ; 
 int zfApFindSta (int /*<<< orphan*/ *,int*) ; 
 size_t zfGetEncryModeFromRxStatus (struct zsAdditionInfo*) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int zmw_rx_buf_readh (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

void zfGetRxIvIcvLength(zdev_t* dev, zbuf_t* buf, u8_t vap, u16_t* pIvLen,
                        u16_t* pIcvLen, struct zsAdditionInfo* addInfo)
{
    u16_t wdsPort;
    u8_t  encryMode;

    zmw_get_wlan_dev(dev);

    *pIvLen = 0;
    *pIcvLen = 0;

    encryMode = zfGetEncryModeFromRxStatus(addInfo);

    if ( wd->wlanMode == ZM_MODE_AP )
    {
        if (vap < ZM_MAX_AP_SUPPORT)
        {
            if (( wd->ap.encryMode[vap] == ZM_WEP64 ) ||
                    ( wd->ap.encryMode[vap] == ZM_WEP128 ) ||
                    ( wd->ap.encryMode[vap] == ZM_WEP256 ))
            {
                *pIvLen = 4;
                *pIcvLen = 4;
            }
            else
            {
                u16_t id;
                u16_t addr[3];

                addr[0] = zmw_rx_buf_readh(dev, buf, ZM_WLAN_HEADER_A2_OFFSET);
                addr[1] = zmw_rx_buf_readh(dev, buf, ZM_WLAN_HEADER_A2_OFFSET+2);
                addr[2] = zmw_rx_buf_readh(dev, buf, ZM_WLAN_HEADER_A2_OFFSET+4);

                /* Find STA's information */
                if ((id = zfApFindSta(dev, addr)) != 0xffff)
                {
                    if (wd->ap.staTable[id].encryMode == ZM_TKIP)
                    {
                        *pIvLen = 8;
                        *pIcvLen = 4;
                    }
                    else if (wd->ap.staTable[id].encryMode == ZM_AES)
                    {
                        *pIvLen = 8;
                        *pIcvLen = 8; // AES MIC
                        //*pIcvLen = 0;
                    }
#ifdef ZM_ENABLE_CENC
                    else if (wd->ap.staTable[id].encryMode == ZM_CENC)
                    {
                        *pIvLen = 18;
                        *pIcvLen= 16;
                    }
#endif //ZM_ENABLE_CENC
                }
            }
            /* WDS port checking */
            if ((wdsPort = vap - 0x20) >= ZM_MAX_WDS_SUPPORT)
            {
                wdsPort = 0;
            }

            switch (wd->ap.wds.encryMode[wdsPort])
			{
			case ZM_WEP64:
			case ZM_WEP128:
			case ZM_WEP256:
                *pIvLen = 4;
                *pIcvLen = 4;
				break;
			case ZM_TKIP:
                *pIvLen = 8;
                *pIcvLen = 4;
				break;
			case ZM_AES:
                *pIvLen = 8;
                *pIcvLen = 0;
				break;
#ifdef ZM_ENABLE_CENC
            case ZM_CENC:
                *pIvLen = 18;
                *pIcvLen = 16;
				break;
#endif //ZM_ENABLE_CENC
			}/* end of switch */
        }
    }
	else if ( wd->wlanMode == ZM_MODE_PSEUDO)
    {
        /* test: 6518 for QA auto test */
        switch (encryMode)
		{
        case ZM_WEP64:
        case ZM_WEP128:
        case ZM_WEP256:
            *pIvLen = 4;
            *pIcvLen = 4;
			break;
		case ZM_TKIP:
            *pIvLen = 8;
            *pIcvLen = 4;
			break;
		case ZM_AES:
            *pIvLen = 8;
            *pIcvLen = 0;
			break;
#ifdef ZM_ENABLE_CENC
        case ZM_CENC:
            *pIvLen = 18;
            *pIcvLen = 16;
#endif //ZM_ENABLE_CENC
		}/* end of switch */
    }
    else
    {
        if ( (encryMode == ZM_WEP64)||
             (encryMode == ZM_WEP128)||
             (encryMode == ZM_WEP256) )
        {
            *pIvLen = 4;
            *pIcvLen = 4;
        }
        else if ( encryMode == ZM_TKIP )
        {
            *pIvLen = 8;
            *pIcvLen = 4;
        }
        else if ( encryMode == ZM_AES )
        {
            *pIvLen = 8;
            *pIcvLen = 8; // AES MIC
        }
#ifdef ZM_ENABLE_CENC
        else if ( encryMode == ZM_CENC)
        {
            *pIvLen = 18;
            *pIcvLen= 16;
        }
#endif //ZM_ENABLE_CENC
    }
}