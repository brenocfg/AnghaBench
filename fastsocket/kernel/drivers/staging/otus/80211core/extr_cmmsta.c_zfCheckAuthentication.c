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
typedef  int /*<<< orphan*/  u8_t ;
typedef  int u16_t ;
struct zsBssInfo {int* rsnIe; int* wpaIe; int /*<<< orphan*/  securityType; int /*<<< orphan*/ * wscIe; } ;
struct TYPE_3__ {scalar_t__ ssidLen; int authMode; int currentAuthMode; void* wepStatus; } ;
struct TYPE_4__ {TYPE_1__ sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
#define  ZM_AUTH_MODE_AUTO 137 
#define  ZM_AUTH_MODE_OPEN 136 
#define  ZM_AUTH_MODE_SHARED_KEY 135 
#define  ZM_AUTH_MODE_WPA 134 
#define  ZM_AUTH_MODE_WPA2 133 
#define  ZM_AUTH_MODE_WPA2PSK 132 
#define  ZM_AUTH_MODE_WPAPSK 131 
#define  ZM_AUTH_MODE_WPAPSK_AUTO 130 
#define  ZM_AUTH_MODE_WPA_AUTO 129 
#define  ZM_AUTH_MODE_WPA_NONE 128 
 void* ZM_ENCRYPTION_AES ; 
 void* ZM_ENCRYPTION_TKIP ; 
 int /*<<< orphan*/  ZM_SECURITY_TYPE_WPA ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfCheckWPAAuth (int /*<<< orphan*/ *,struct zsBssInfo*) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u8_t zfCheckAuthentication(zdev_t* dev, struct zsBssInfo* pBssInfo)
{
    u8_t   ret=TRUE;
    u16_t  encAlgoType;
    u16_t UnicastCipherNum;

    zmw_get_wlan_dev(dev);

    /* Connecting to ANY has been checked */
    if ( wd->sta.ssidLen == 0 )
    {
        return ret;
    }


	switch(wd->sta.authMode)
	//switch(wd->ws.authMode)//Quickly reboot
    {
        case ZM_AUTH_MODE_WPA_AUTO:
        case ZM_AUTH_MODE_WPAPSK_AUTO:
            encAlgoType = 0;
            if(pBssInfo->rsnIe[1] != 0)
            {
                UnicastCipherNum = (pBssInfo->rsnIe[8]) +
                                   (pBssInfo->rsnIe[9] << 8);

                /* If there is only one unicast cipher */
                if (UnicastCipherNum == 1)
                {
                    encAlgoType = pBssInfo->rsnIe[13];
                    //encAlgoType = pBssInfo->rsnIe[7];
                }
                else
                {
                    u16_t ii;
                    u16_t desiredCipher = 0;
                    u16_t IEOffSet = 13;

                    /* Enumerate all the supported unicast cipher */
                    for (ii = 0; ii < UnicastCipherNum; ii++)
                    {
                        if (pBssInfo->rsnIe[IEOffSet+ii*4] > desiredCipher)
                        {
                            desiredCipher = pBssInfo->rsnIe[IEOffSet+ii*4];
                        }
                    }

                    encAlgoType = desiredCipher;
                }

                if ( encAlgoType == 0x02 )
                {
    			    wd->sta.wepStatus = ZM_ENCRYPTION_TKIP;

    			    if ( wd->sta.authMode == ZM_AUTH_MODE_WPA_AUTO )
                    {
                        wd->sta.currentAuthMode = ZM_AUTH_MODE_WPA2;
                    }
                    else //ZM_AUTH_MODE_WPAPSK_AUTO
                    {
                        wd->sta.currentAuthMode = ZM_AUTH_MODE_WPA2PSK;
                    }
                }
                else if ( encAlgoType == 0x04 )
                {
                    wd->sta.wepStatus = ZM_ENCRYPTION_AES;

                    if ( wd->sta.authMode == ZM_AUTH_MODE_WPA_AUTO )
                    {
                        wd->sta.currentAuthMode = ZM_AUTH_MODE_WPA2;
                    }
                    else //ZM_AUTH_MODE_WPAPSK_AUTO
                    {
                        wd->sta.currentAuthMode = ZM_AUTH_MODE_WPA2PSK;
                    }
                }
                else
                {
                    ret = FALSE;
                }
            }
            else if(pBssInfo->wpaIe[1] != 0)
            {
                UnicastCipherNum = (pBssInfo->wpaIe[12]) +
                                   (pBssInfo->wpaIe[13] << 8);

                /* If there is only one unicast cipher */
                if (UnicastCipherNum == 1)
                {
                    encAlgoType = pBssInfo->wpaIe[17];
                    //encAlgoType = pBssInfo->wpaIe[11];
                }
                else
                {
                    u16_t ii;
                    u16_t desiredCipher = 0;
                    u16_t IEOffSet = 17;

                    /* Enumerate all the supported unicast cipher */
                    for (ii = 0; ii < UnicastCipherNum; ii++)
                    {
                        if (pBssInfo->wpaIe[IEOffSet+ii*4] > desiredCipher)
                        {
                            desiredCipher = pBssInfo->wpaIe[IEOffSet+ii*4];
                        }
                    }

                    encAlgoType = desiredCipher;
                }

                if ( encAlgoType == 0x02 )
                {
    			    wd->sta.wepStatus = ZM_ENCRYPTION_TKIP;

    			    if ( wd->sta.authMode == ZM_AUTH_MODE_WPA_AUTO )
                    {
                        wd->sta.currentAuthMode = ZM_AUTH_MODE_WPA;
                    }
                    else //ZM_AUTH_MODE_WPAPSK_AUTO
                    {
                        wd->sta.currentAuthMode = ZM_AUTH_MODE_WPAPSK;
                    }
                }
                else if ( encAlgoType == 0x04 )
                {
                    wd->sta.wepStatus = ZM_ENCRYPTION_AES;

                    if ( wd->sta.authMode == ZM_AUTH_MODE_WPA_AUTO )
                    {
                        wd->sta.currentAuthMode = ZM_AUTH_MODE_WPA;
                    }
                    else //ZM_AUTH_MODE_WPAPSK_AUTO
                    {
                        wd->sta.currentAuthMode = ZM_AUTH_MODE_WPAPSK;
                    }
                }
                else
                {
                    ret = FALSE;
                }


            }
            else
            {
                ret = FALSE;
            }

            break;

        case ZM_AUTH_MODE_WPA:
        case ZM_AUTH_MODE_WPAPSK:
        case ZM_AUTH_MODE_WPA_NONE:
        case ZM_AUTH_MODE_WPA2:
        case ZM_AUTH_MODE_WPA2PSK:
            {
                if ( pBssInfo->securityType != ZM_SECURITY_TYPE_WPA )
                {
                    ret = FALSE;
                }

                ret = zfCheckWPAAuth(dev, pBssInfo);
            }
            break;

        case ZM_AUTH_MODE_OPEN:
        case ZM_AUTH_MODE_SHARED_KEY:
        case ZM_AUTH_MODE_AUTO:
            {
                if ( pBssInfo->wscIe[1] )
                {
                    // If the AP is a Jumpstart AP, it's ok!! Ray
                    break;
                }
                else if ( pBssInfo->securityType == ZM_SECURITY_TYPE_WPA )
                {
                    ret = FALSE;
                }
            }
            break;

        default:
            break;
    }

    return ret;
}