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
typedef  int u8_t ;
typedef  size_t u32_t ;
typedef  int u16_t ;
struct TYPE_6__ {size_t bssidCount; TYPE_1__* bssidInfo; } ;
struct TYPE_7__ {scalar_t__ currentAuthMode; int* wpaIe; scalar_t__ wepStatus; int* rsnIe; TYPE_2__ pmkidInfo; scalar_t__ bssid; } ;
struct TYPE_8__ {TYPE_3__ sta; } ;
struct TYPE_5__ {int* pmkid; scalar_t__ bssid; } ;

/* Variables and functions */
 scalar_t__ ZM_AUTH_MODE_WPA ; 
 scalar_t__ ZM_AUTH_MODE_WPA2 ; 
 scalar_t__ ZM_AUTH_MODE_WPA2PSK ; 
 scalar_t__ ZM_AUTH_MODE_WPAPSK ; 
 scalar_t__ ZM_ENCRYPTION_AES ; 
 int ZM_WLAN_FRAME_TYPE_ASOCREQ ; 
 int ZM_WLAN_FRAME_TYPE_REASOCREQ ; 
 TYPE_4__* wd ; 
 int /*<<< orphan*/  zfCopyToIntTxBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int,int) ; 
 int /*<<< orphan*/  zfMemoryCopy (int*,int*,int) ; 
 scalar_t__ zfMemoryIsEqual (int*,int*,int) ; 
 int* zgWpa2AesOui ; 
 int* zgWpa2RadiusOui ; 
 int* zgWpaAesOui ; 
 int* zgWpaRadiusOui ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u16_t zfStaAddIeWpaRsn(zdev_t* dev, zbuf_t* buf, u16_t offset, u8_t frameType)
{
    u32_t  i;
    u8_t    ssn[64]={
                        /* Element ID */
                        0xdd,
                        /* Length */
                        0x18,
                        /* OUI type */
                        0x00, 0x50, 0xf2, 0x01,
                        /* Version */
                        0x01, 0x00,
                        /* Group Cipher Suite, default=TKIP */
                        0x00, 0x50, 0xf2, 0x02,
                        /* Pairwise Cipher Suite Count */
                        0x01, 0x00,
                        /* Pairwise Cipher Suite, default=TKIP */
                        0x00, 0x50, 0xf2, 0x02,
                        /* Authentication and Key Management Suite Count */
                        0x01, 0x00,
                        /* Authentication type, default=PSK */
                        0x00, 0x50, 0xf2, 0x02,
                        /* WPA capability */
                        0x00, 0x00
                    };

    u8_t    rsn[64]={
                        /* Element ID */
                        0x30,
                        /* Length */
                        0x14,
                        /* Version */
                        0x01, 0x00,
                        /* Group Cipher Suite, default=TKIP */
                        0x00, 0x0f, 0xac, 0x02,
                        /* Pairwise Cipher Suite Count */
                        0x01, 0x00,
                        /* Pairwise Cipher Suite, default=TKIP */
                        0x00, 0x0f, 0xac, 0x02,
                        /* Authentication and Key Management Suite Count */
                        0x01, 0x00,
                        /* Authentication type, default=PSK */
                        0x00, 0x0f, 0xac, 0x02,
                        /* RSN capability */
                        0x00, 0x00
                    };

    zmw_get_wlan_dev(dev);

    if ( wd->sta.currentAuthMode == ZM_AUTH_MODE_WPAPSK )
    {
        /* Overwrite Group Cipher Suite by AP's setting */
        zfMemoryCopy(ssn+8, wd->sta.wpaIe+8, 4);

        if ( wd->sta.wepStatus == ZM_ENCRYPTION_AES )
        {
            /* Overwrite Pairwise Cipher Suite by AES */
            zfMemoryCopy(ssn+14, zgWpaAesOui, 4);
        }

        zfCopyToIntTxBuffer(dev, buf, ssn, offset, ssn[1]+2);
        zfMemoryCopy(wd->sta.wpaIe, ssn, ssn[1]+2);
        offset += (ssn[1]+2);
    }
    else if ( wd->sta.currentAuthMode == ZM_AUTH_MODE_WPA )
    {
        /* Overwrite Group Cipher Suite by AP's setting */
        zfMemoryCopy(ssn+8, wd->sta.wpaIe+8, 4);
        /* Overwrite Key Management Suite by WPA-Radius */
        zfMemoryCopy(ssn+20, zgWpaRadiusOui, 4);

        if ( wd->sta.wepStatus == ZM_ENCRYPTION_AES )
        {
            /* Overwrite Pairwise Cipher Suite by AES */
            zfMemoryCopy(ssn+14, zgWpaAesOui, 4);
        }

        zfCopyToIntTxBuffer(dev, buf, ssn, offset, ssn[1]+2);
        zfMemoryCopy(wd->sta.wpaIe, ssn, ssn[1]+2);
        offset += (ssn[1]+2);
    }
    else if ( wd->sta.currentAuthMode == ZM_AUTH_MODE_WPA2PSK )
    {
        /* Overwrite Group Cipher Suite by AP's setting */
        zfMemoryCopy(rsn+4, wd->sta.rsnIe+4, 4);

        if ( wd->sta.wepStatus == ZM_ENCRYPTION_AES )
        {
            /* Overwrite Pairwise Cipher Suite by AES */
            zfMemoryCopy(rsn+10, zgWpa2AesOui, 4);
        }

        if ( frameType == ZM_WLAN_FRAME_TYPE_REASOCREQ )
        {
            for(i=0; i<wd->sta.pmkidInfo.bssidCount; i++)
            {
                if ( zfMemoryIsEqual((u8_t*) wd->sta.pmkidInfo.bssidInfo[i].bssid,
                                     (u8_t*) wd->sta.bssid, 6) )
                {
                    /* matched */
                    break;
                }

                if ( i < wd->sta.pmkidInfo.bssidCount )
                {
                    // Fill PMKID Count in RSN information element
                    rsn[22] = 0x01;
                    rsn[23] = 0x00;

                    // Fill PMKID in RSN information element
                    zfMemoryCopy(rsn+24,
                                 wd->sta.pmkidInfo.bssidInfo[i].pmkid, 16);
			                 rsn[1] += 18;
                }
            }
        }

        zfCopyToIntTxBuffer(dev, buf, rsn, offset, rsn[1]+2);
        zfMemoryCopy(wd->sta.rsnIe, rsn, rsn[1]+2);
        offset += (rsn[1]+2);
    }
    else if ( wd->sta.currentAuthMode == ZM_AUTH_MODE_WPA2 )
    {
        /* Overwrite Group Cipher Suite by AP's setting */
        zfMemoryCopy(rsn+4, wd->sta.rsnIe+4, 4);
        /* Overwrite Key Management Suite by WPA2-Radius */
        zfMemoryCopy(rsn+16, zgWpa2RadiusOui, 4);

        if ( wd->sta.wepStatus == ZM_ENCRYPTION_AES )
        {
            /* Overwrite Pairwise Cipher Suite by AES */
            zfMemoryCopy(rsn+10, zgWpa2AesOui, 4);
        }

        if (( frameType == ZM_WLAN_FRAME_TYPE_REASOCREQ || ( frameType == ZM_WLAN_FRAME_TYPE_ASOCREQ )))
        {

            if (wd->sta.pmkidInfo.bssidCount != 0) {
                // Fill PMKID Count in RSN information element
                rsn[22] = 1;
                rsn[23] = 0;
                /*
                 *  The caller is respnsible to give us the relevant PMKID.
                 *  We'll only accept 1 PMKID for now.
                 */
                for(i=0; i<wd->sta.pmkidInfo.bssidCount; i++)
                {
                    if ( zfMemoryIsEqual((u8_t*) wd->sta.pmkidInfo.bssidInfo[i].bssid, (u8_t*) wd->sta.bssid, 6) )
                    {
                        zfMemoryCopy(rsn+24, wd->sta.pmkidInfo.bssidInfo[i].pmkid, 16);
                        break;
                    }
                }
                rsn[1] += 18;
            }

        }

        zfCopyToIntTxBuffer(dev, buf, rsn, offset, rsn[1]+2);
        zfMemoryCopy(wd->sta.rsnIe, rsn, rsn[1]+2);
        offset += (rsn[1]+2);
    }

    return offset;
}