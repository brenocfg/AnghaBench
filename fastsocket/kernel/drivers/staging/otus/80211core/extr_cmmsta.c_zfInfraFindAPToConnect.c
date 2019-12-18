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
typedef  int u32_t ;
typedef  scalar_t__ u16_t ;
struct zsBssInfo {int* capability; scalar_t__* ssid; scalar_t__ securityType; scalar_t__* bssid; int frequency; int EnableHT; int apCap; int enableHT40; scalar_t__* extSupportedRates; struct zsBssInfo* next; int /*<<< orphan*/  wmeSupport; } ;
struct TYPE_4__ {scalar_t__ bssCount; struct zsBssInfo* head; } ;
struct TYPE_5__ {scalar_t__ ssidLen; scalar_t__ wepStatus; int dropUnencryptedPkts; scalar_t__ authMode; scalar_t__ bDesiredBssid; scalar_t__* desiredBssid; int /*<<< orphan*/  apWmeCapability; int /*<<< orphan*/  ssid; TYPE_1__ bssList; } ;
struct TYPE_6__ {int connectMode; TYPE_2__ sta; } ;

/* Variables and functions */
 int CHANNEL_A ; 
 int CHANNEL_A_HT ; 
 int CHANNEL_B ; 
 int CHANNEL_G ; 
 int CHANNEL_G_HT ; 
 int CHANNEL_HT20 ; 
 int CHANNEL_HT40 ; 
 scalar_t__ TRUE ; 
 scalar_t__ ZM_AUTH_MODE_AUTO ; 
 scalar_t__ ZM_AUTH_MODE_OPEN ; 
 int ZM_All11N_AP ; 
 int ZM_BIT_0 ; 
 int ZM_BIT_1 ; 
 int ZM_BIT_2 ; 
 int ZM_BIT_3 ; 
 int ZM_BIT_4 ; 
 scalar_t__ ZM_ENCRYPTION_WEP_DISABLED ; 
 scalar_t__ ZM_ENCRYPTION_WEP_ENABLED ; 
 int /*<<< orphan*/  ZM_LV_0 ; 
 int /*<<< orphan*/  ZM_LV_1 ; 
 scalar_t__ ZM_SECURITY_TYPE_WPA ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfCheckAuthentication (int /*<<< orphan*/ *,struct zsBssInfo*) ; 
 scalar_t__ zfMemoryIsEqual (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ zfStaIsApInBlockingList (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  zfwMemoryCopy (void*,void*,int) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zm_msg0_mm (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct zsBssInfo* zfInfraFindAPToConnect(zdev_t* dev,
        struct zsBssInfo* candidateBss)
{
    struct zsBssInfo* pBssInfo;
    struct zsBssInfo* pNowBssInfo=NULL;
    u16_t i;
    u16_t ret, apWepStatus;
    u32_t k;
    u32_t channelFlags;

    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);

    pBssInfo = wd->sta.bssList.head;

    for(i=0; i<wd->sta.bssList.bssCount; i++)
    {
        if ( pBssInfo->capability[0] & ZM_BIT_4 )
        {
            apWepStatus = ZM_ENCRYPTION_WEP_ENABLED;
        }
        else
        {
            apWepStatus = ZM_ENCRYPTION_WEP_DISABLED;
        }

        if ( ((zfMemoryIsEqual(&(pBssInfo->ssid[2]), wd->sta.ssid,
                               wd->sta.ssidLen))&&
              (wd->sta.ssidLen == pBssInfo->ssid[1]))||
             ((wd->sta.ssidLen == 0)&&
               /* connect to any BSS: AP's ans STA's WEP status must match */
              (wd->sta.wepStatus == apWepStatus )&&
              (pBssInfo->securityType != ZM_SECURITY_TYPE_WPA) ))
        {
            if ( wd->sta.ssidLen == 0 )
            {
                zm_debug_msg0("ANY BSS found");
            }

            if ( ((wd->sta.wepStatus == ZM_ENCRYPTION_WEP_DISABLED && apWepStatus == ZM_ENCRYPTION_WEP_ENABLED) ||
                 (wd->sta.wepStatus == ZM_ENCRYPTION_WEP_ENABLED &&
                 (apWepStatus == ZM_ENCRYPTION_WEP_DISABLED && wd->sta.dropUnencryptedPkts == 1))) &&
                 (wd->sta.authMode >= ZM_AUTH_MODE_OPEN && wd->sta.authMode <= ZM_AUTH_MODE_AUTO) )
            {
                zm_debug_msg0("Privacy policy is inconsistent");
                pBssInfo = pBssInfo->next;
                continue;
            }

            /* for WPA negative test */
            if ( !zfCheckAuthentication(dev, pBssInfo) )
            {
                pBssInfo = pBssInfo->next;
                continue;
            }

            /* Check bssid */
            if (wd->sta.bDesiredBssid == TRUE)
            {
                for (k=0; k<6; k++)
                {
                    if (wd->sta.desiredBssid[k] != pBssInfo->bssid[k])
                    {
                        zm_msg0_mm(ZM_LV_1, "desired bssid not matched 1");
                        break;
                    }
                }

                if (k != 6)
                {
                    zm_msg0_mm(ZM_LV_1, "desired bssid not matched 2");
                    pBssInfo = pBssInfo->next;
                    continue;
                }
            }

            /* Check support mode */
            if (pBssInfo->frequency > 3000) {
                if (   (pBssInfo->EnableHT == 1)
                    || (pBssInfo->apCap & ZM_All11N_AP) ) //11n AP
                {
                    channelFlags = CHANNEL_A_HT;
                    if (pBssInfo->enableHT40 == 1) {
                        channelFlags |= CHANNEL_HT40;
                    }
                } else {
                    channelFlags = CHANNEL_A;
                }
            } else {
                if (   (pBssInfo->EnableHT == 1)
                    || (pBssInfo->apCap & ZM_All11N_AP) ) //11n AP
                {
                    channelFlags = CHANNEL_G_HT;
                    if(pBssInfo->enableHT40 == 1) {
                        channelFlags |= CHANNEL_HT40;
                    }
                } else {
                    if (pBssInfo->extSupportedRates[1] == 0) {
                        channelFlags = CHANNEL_B;
                    } else {
                        channelFlags = CHANNEL_G;
                    }
                }
            }

            if (   ((channelFlags == CHANNEL_B) && (wd->connectMode & ZM_BIT_0))
                || ((channelFlags == CHANNEL_G) && (wd->connectMode & ZM_BIT_1))
                || ((channelFlags == CHANNEL_A) && (wd->connectMode & ZM_BIT_2))
                || ((channelFlags & CHANNEL_HT20) && (wd->connectMode & ZM_BIT_3)) )
            {
                pBssInfo = pBssInfo->next;
                continue;
            }

            /* Skip if AP in blocking list */
            if ((ret = zfStaIsApInBlockingList(dev, pBssInfo->bssid)) == TRUE)
            {
                zm_msg0_mm(ZM_LV_0, "Candidate AP in blocking List, skip if there's stilla choice!");
                pNowBssInfo = pBssInfo;
                pBssInfo = pBssInfo->next;
                continue;
            }

            if ( pBssInfo->capability[0] & ZM_BIT_0 )  // check if infra-BSS
            {
                    pNowBssInfo = pBssInfo;
                    wd->sta.apWmeCapability = pBssInfo->wmeSupport;


                    goto done;
            }
        }

        pBssInfo = pBssInfo->next;
    }

done:
    if (pNowBssInfo != NULL)
    {
        zfwMemoryCopy((void*)candidateBss, (void*)pNowBssInfo, sizeof(struct zsBssInfo));
        pNowBssInfo = candidateBss;
    }

    zmw_leave_critical_section(dev);

    return pNowBssInfo;
}