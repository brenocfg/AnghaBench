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
typedef  void* u8_t ;
typedef  int u16_t ;
struct zsBssInfo {scalar_t__* ssid; int* beaconInterval; int EnableHT; scalar_t__ securityType; scalar_t__* cencIe; scalar_t__* wpaIe; scalar_t__* rsnIe; int* capability; int enableHT40; int extChOffset; int athOwlAp; int erp; int marvelAp; int frameBodysize; int* timeStamp; int* frameBody; int /*<<< orphan*/  macaddr; int /*<<< orphan*/  SG40; int /*<<< orphan*/  extSupportedRates; int /*<<< orphan*/  supportedRates; int /*<<< orphan*/  bssid; int /*<<< orphan*/  frequency; } ;
struct TYPE_4__ {scalar_t__ tempWakeUp; } ;
struct TYPE_5__ {scalar_t__ SWEncryptEnable; scalar_t__ bSafeMode; scalar_t__ ssidLen; int* capability; int EnableHT; scalar_t__ wepStatus; int athOwlAp; int enableDrvBA; int beaconFrameBodySize; int* beaconFrameBody; scalar_t__ authMode; int connectTimeoutCount; int bIsSharedKey; int /*<<< orphan*/  bssid; void* bProtectionMode; scalar_t__* rsnIe; scalar_t__* wpaIe; int /*<<< orphan*/  encryMode; void* wpaState; scalar_t__* cencIe; scalar_t__ wmeEnabled; int /*<<< orphan*/  SG40; scalar_t__* ssid; int /*<<< orphan*/  connectState; int /*<<< orphan*/  uapsdQ; scalar_t__ qosInfo; TYPE_1__ psMgr; scalar_t__ wmeConnected; scalar_t__ bssNotFoundCount; } ;
struct TYPE_6__ {int beaconInterval; scalar_t__ preambleTypeInUsed; scalar_t__ preambleType; int BandWidth40; int ExtOffset; int reorder; TYPE_2__ sta; int /*<<< orphan*/  frequency; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  NdisCENC_PSK ; 
 void* TRUE ; 
 int /*<<< orphan*/  ZM_AES ; 
 scalar_t__ ZM_AUTH_MODE_AUTO ; 
 scalar_t__ ZM_AUTH_MODE_OPEN ; 
 scalar_t__ ZM_AUTH_MODE_SHARED_KEY ; 
 int ZM_BIT_0 ; 
 int ZM_BIT_1 ; 
 int ZM_BIT_2 ; 
 int ZM_BIT_4 ; 
 int ZM_BIT_5 ; 
 int ZM_CACHED_FRAMEBODY_SIZE ; 
 int /*<<< orphan*/  ZM_DEFAULT_SUPPORT_RATE_ZERO ; 
 scalar_t__ ZM_ENCRYPTION_AES ; 
 scalar_t__ ZM_ENCRYPTION_TKIP ; 
 scalar_t__ ZM_ENCRYPTION_WEP_DISABLED ; 
 scalar_t__ ZM_ENCRYPTION_WEP_ENABLED ; 
 void* ZM_MPDU_DENSITY_8US ; 
 void* ZM_MPDU_DENSITY_NONE ; 
 scalar_t__ ZM_PREAMBLE_TYPE_AUTO ; 
 scalar_t__ ZM_PREAMBLE_TYPE_LONG ; 
 scalar_t__ ZM_PREAMBLE_TYPE_SHORT ; 
 scalar_t__ ZM_SECURITY_TYPE_CENC ; 
 scalar_t__ ZM_SECURITY_TYPE_WPA ; 
 int /*<<< orphan*/  ZM_STATUS_MEDIA_DISCONNECT_NOT_FOUND ; 
 int /*<<< orphan*/  ZM_STA_CONN_STATE_NONE ; 
 int /*<<< orphan*/  ZM_STA_STATE_CONNECTING ; 
 void* ZM_STA_WPA_STATE_INIT ; 
 int ZM_SW_TKIP_DECRY_EN ; 
 int ZM_SW_TKIP_ENCRY_EN ; 
 int ZM_SW_WEP_DECRY_EN ; 
 int ZM_SW_WEP_ENCRY_EN ; 
 int /*<<< orphan*/  ZM_TKIP ; 
 int /*<<< orphan*/  cencInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cencSetCENCMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfBssInfoReorderList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfChangeAdapterState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfCoreSetFrequencyV2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfHpDisableHwRetry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfHpEnableHwRetry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfHpSetMPDUDensity (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  zfHpSetSlotTime (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfHpSetSlotTimeRegister (int /*<<< orphan*/ *,int) ; 
 struct zsBssInfo* zfInfraFindAPToConnect (int /*<<< orphan*/ *,struct zsBssInfo*) ; 
 int /*<<< orphan*/  zfMemoryCopy (scalar_t__*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  zfPowerSavingMgrWakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfQueueFlush (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfResetSupportRate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfStaConnectFail (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfStaDisableSWEncryption (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfStaEnableSWEncryption (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfStaRefreshBlockList (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfStaStartConnectCb ; 
 int /*<<< orphan*/  zfUpdateBssid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfUpdateDefaultQosParameter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfUpdateSupportRate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfwCencHandleBeaconProbrespon (int /*<<< orphan*/ *,void**,void**,void**) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfInfraConnectNetwork(zdev_t* dev)
{
    struct zsBssInfo* pBssInfo;
    struct zsBssInfo* pNowBssInfo=NULL;
    struct zsBssInfo candidateBss;
    //u16_t i, j=100, quality=10000;
    //u8_t ret=FALSE, apWepStatus;
    u8_t ret=FALSE;
    u16_t k;
    u8_t density = ZM_MPDU_DENSITY_NONE;

    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();

    /* Reset bssNotFoundCount for Ad-Hoc:IBSS */
    /* Need review : IbssConn -> InfraConn -> IbssConn etc, flag/counter reset? */
    zmw_enter_critical_section(dev);
    wd->sta.bssNotFoundCount = 0;
    zmw_leave_critical_section(dev);

    /* Set TxQs CWMIN, CWMAX, AIFS and TXO to WME STA default. */
    zfUpdateDefaultQosParameter(dev, 0);

    zfStaRefreshBlockList(dev, 0);

    /* change state to CONNECTING and stop the channel scanning */
    zfChangeAdapterState(dev, ZM_STA_STATE_CONNECTING);
    zfPowerSavingMgrWakeup(dev);

    wd->sta.wmeConnected = 0;
    wd->sta.psMgr.tempWakeUp = 0;
    wd->sta.qosInfo = 0;
    zfQueueFlush(dev, wd->sta.uapsdQ);

    wd->sta.connectState = ZM_STA_CONN_STATE_NONE;

    //Reorder BssList by RSSI--CWYang(+)
    zfBssInfoReorderList(dev);

    pNowBssInfo = zfInfraFindAPToConnect(dev, &candidateBss);

	if (wd->sta.SWEncryptEnable != 0)
	{
	    if (wd->sta.bSafeMode == 0)
	    {
		    zfStaDisableSWEncryption(dev);//Quickly reboot
	    }
	}
    if ( pNowBssInfo != NULL )
    {
        //zm_assert(pNowBssInfo != NULL);

        pBssInfo = pNowBssInfo;
        wd->sta.ssidLen = pBssInfo->ssid[1];
        zfMemoryCopy(wd->sta.ssid, &(pBssInfo->ssid[2]), pBssInfo->ssid[1]);
        wd->frequency = pBssInfo->frequency;
        //wd->sta.flagFreqChanging = 1;

        //zfCoreSetFrequency(dev, wd->frequency);
        zfUpdateBssid(dev, pBssInfo->bssid);
        zfResetSupportRate(dev, ZM_DEFAULT_SUPPORT_RATE_ZERO);
        zfUpdateSupportRate(dev, pBssInfo->supportedRates);
        zfUpdateSupportRate(dev, pBssInfo->extSupportedRates);

        wd->beaconInterval = pBssInfo->beaconInterval[0] +
                             (((u16_t) pBssInfo->beaconInterval[1]) << 8);
        if (wd->beaconInterval == 0)
        {
            wd->beaconInterval = 100;
        }

        /* ESS bit on */
        wd->sta.capability[0] |= ZM_BIT_0;
        /* IBSS bit off */
        wd->sta.capability[0] &= ~ZM_BIT_1;

        /* 11n AP flag */
        wd->sta.EnableHT = pBssInfo->EnableHT;
        wd->sta.SG40 = pBssInfo->SG40;
#ifdef ZM_ENABLE_CENC
        if ( pBssInfo->securityType == ZM_SECURITY_TYPE_CENC )
        {
            wd->sta.wmeEnabled = 0; //Disable WMM in CENC
            cencInit(dev);
            cencSetCENCMode(dev, NdisCENC_PSK);
            wd->sta.wpaState = ZM_STA_WPA_STATE_INIT;
            /* CENC */
            if ( pBssInfo->cencIe[1] != 0 )
            {
                //wd->sta.wepStatus = ZM_ENCRYPTION_CENC;
                //wd->sta.encryMode = ZM_CENC;
                zfwCencHandleBeaconProbrespon(dev, (u8_t *)&pBssInfo->cencIe,
                        (u8_t *)&pBssInfo->ssid, (u8_t *)&pBssInfo->macaddr);
                zfMemoryCopy(wd->sta.cencIe, pBssInfo->cencIe,
                        pBssInfo->cencIe[1]+2);
            }
            else
            {
                wd->sta.cencIe[1] = 0;
            }
        }
#endif //ZM_ENABLE_CENC
        if ( pBssInfo->securityType == ZM_SECURITY_TYPE_WPA )
        {
            wd->sta.wpaState = ZM_STA_WPA_STATE_INIT;

            if ( wd->sta.wepStatus == ZM_ENCRYPTION_TKIP )
            {
                wd->sta.encryMode = ZM_TKIP;

                /* Turn on software encryption/decryption for TKIP */
                if (wd->sta.EnableHT == 1)
                {
                    zfStaEnableSWEncryption(dev, (ZM_SW_TKIP_ENCRY_EN|ZM_SW_TKIP_DECRY_EN));
                }

                /* Do not support TKIP in 11n mode */
                //wd->sta.EnableHT = 0;
                //pBssInfo->enableHT40 = 0;
            }
            else if ( wd->sta.wepStatus == ZM_ENCRYPTION_AES )
            {
                wd->sta.encryMode = ZM_AES;

                /* If AP supports HT mode */
                if (wd->sta.EnableHT)
                {
                    /* Set MPDU density to 8 us*/
                    density = ZM_MPDU_DENSITY_8US;
                }
            }

            if ( pBssInfo->wpaIe[1] != 0 )
            {
                zfMemoryCopy(wd->sta.wpaIe, pBssInfo->wpaIe,
                             pBssInfo->wpaIe[1]+2);
            }
            else
            {
                wd->sta.wpaIe[1] = 0;
            }

            if ( pBssInfo->rsnIe[1] != 0 )
            {
                zfMemoryCopy(wd->sta.rsnIe, pBssInfo->rsnIe,
                             pBssInfo->rsnIe[1]+2);
            }
            else
            {
                wd->sta.rsnIe[1] = 0;
            }
        }



        /* check preamble bit */
        wd->preambleTypeInUsed = wd->preambleType;
        if ( wd->preambleTypeInUsed == ZM_PREAMBLE_TYPE_AUTO )
        {
            if (pBssInfo->capability[0] & ZM_BIT_5)
            {
                wd->preambleTypeInUsed = ZM_PREAMBLE_TYPE_SHORT;
            }
            else
            {
                wd->preambleTypeInUsed = ZM_PREAMBLE_TYPE_LONG;
            }
        }

        if (wd->preambleTypeInUsed == ZM_PREAMBLE_TYPE_LONG)
        {
            wd->sta.capability[0] &= ~ZM_BIT_5;
        }
        else
        {
            wd->sta.capability[0] |= ZM_BIT_5;
        }

        /* check 802.11n 40MHz Setting */
        if ((pBssInfo->enableHT40 == 1) &&
            ((pBssInfo->extChOffset == 1) || (pBssInfo->extChOffset == 3)))
        {
            wd->BandWidth40 = pBssInfo->enableHT40;
            wd->ExtOffset = pBssInfo->extChOffset;
        }
        else
        {
            wd->BandWidth40 = 0;
            wd->ExtOffset = 0;
        }

        /* check 802.11H support bit */

        /* check Owl Ap */
        if ( pBssInfo->athOwlAp & ZM_BIT_0 )
        {
            /* In this function, FW retry will be enable, ZM_MAC_REG_RETRY_MAX
               will be set to 0.
             */
            zfHpDisableHwRetry(dev);
            wd->sta.athOwlAp = 1;
            /* Set MPDU density to 8 us*/
            density = ZM_MPDU_DENSITY_8US;
        }
        else
        {
            /* In this function, FW retry will be disable, ZM_MAC_REG_RETRY_MAX
               will be set to 3.
             */
            zfHpEnableHwRetry(dev);
            wd->sta.athOwlAp = 0;
        }
        wd->reorder = 1;

        /* Set MPDU density */
        zfHpSetMPDUDensity(dev, density);

        /* check short slot time bit */
        if ( pBssInfo->capability[1] & ZM_BIT_2 )
        {
            wd->sta.capability[1] |= ZM_BIT_2;
        }

        if ( pBssInfo->erp & ZM_BIT_1 )
        {
            //zm_debug_msg0("protection mode on");
            wd->sta.bProtectionMode = TRUE;
            zfHpSetSlotTime(dev, 0);
        }
        else
        {
            //zm_debug_msg0("protection mode off");
            wd->sta.bProtectionMode = FALSE;
            zfHpSetSlotTime(dev, 1);
        }

        if (pBssInfo->marvelAp == 1)
        {
            wd->sta.enableDrvBA = 0;
            /*
             * 8701 : NetGear 3500 (MARVELL)
             * Downlink issue : set slottime to 20.
             */
            zfHpSetSlotTimeRegister(dev, 0);
        }
        else
        {
            wd->sta.enableDrvBA = 1;

            /*
             * This is not good for here do reset slot time.
             * I think it should reset when leave MARVELL ap
             * or enter disconnect state etc.
             */
            zfHpSetSlotTimeRegister(dev, 1);
        }

        //Store probe response frame body, for VISTA only
        wd->sta.beaconFrameBodySize = pBssInfo->frameBodysize + 12;
        if (wd->sta.beaconFrameBodySize > ZM_CACHED_FRAMEBODY_SIZE)
        {
            wd->sta.beaconFrameBodySize = ZM_CACHED_FRAMEBODY_SIZE;
        }
        for (k=0; k<8; k++)
        {
            wd->sta.beaconFrameBody[k] = pBssInfo->timeStamp[k];
        }
        wd->sta.beaconFrameBody[8] = pBssInfo->beaconInterval[0];
        wd->sta.beaconFrameBody[9] = pBssInfo->beaconInterval[1];
        wd->sta.beaconFrameBody[10] = pBssInfo->capability[0];
        wd->sta.beaconFrameBody[11] = pBssInfo->capability[1];
        for (k=0; k<(wd->sta.beaconFrameBodySize - 12); k++)
        {
            wd->sta.beaconFrameBody[k+12] = pBssInfo->frameBody[k];
        }

        if ( ( pBssInfo->capability[0] & ZM_BIT_4 )&&
             (( wd->sta.authMode == ZM_AUTH_MODE_OPEN )||
              ( wd->sta.authMode == ZM_AUTH_MODE_SHARED_KEY)||
              (wd->sta.authMode == ZM_AUTH_MODE_AUTO)) )
        {   /* privacy enabled */

            if ( wd->sta.wepStatus == ZM_ENCRYPTION_WEP_DISABLED )
            {
                zm_debug_msg0("Adapter is no WEP, try to connect to WEP AP");
                ret = FALSE;
            }

            /* Do not support WEP in 11n mode */
            if ( wd->sta.wepStatus == ZM_ENCRYPTION_WEP_ENABLED )
            {
                /* Turn on software encryption/decryption for WEP */
                if (wd->sta.EnableHT == 1)
                {
                    zfStaEnableSWEncryption(dev, (ZM_SW_WEP_ENCRY_EN|ZM_SW_WEP_DECRY_EN));
                }

                //wd->sta.EnableHT = 0;
                //wd->BandWidth40 = 0;
                //wd->ExtOffset = 0;
            }

            wd->sta.capability[0] |= ZM_BIT_4;

            if ( wd->sta.authMode == ZM_AUTH_MODE_AUTO )
            { /* Try to use open and shared-key authehtication alternatively */
                if ( (wd->sta.connectTimeoutCount % 2) == 0 )
                    wd->sta.bIsSharedKey = 0;
                else
                    wd->sta.bIsSharedKey = 1;
            }
            else if ( wd->sta.authMode != ZM_AUTH_MODE_SHARED_KEY )
            {   /* open  or auto */
                //zfStaStartConnect(dev, 0);
                wd->sta.bIsSharedKey = 0;
            }
            else if ( wd->sta.authMode != ZM_AUTH_MODE_OPEN )
            {   /* shared key */
                //zfStaStartConnect(dev, 1) ;
                wd->sta.bIsSharedKey = 1;
            }
        }
        else
        {
            if ( (pBssInfo->securityType == ZM_SECURITY_TYPE_WPA)||
                 (pBssInfo->capability[0] & ZM_BIT_4) )
            {
                wd->sta.capability[0] |= ZM_BIT_4;
                /* initialize WPA related parameters */
            }
            else
            {
                wd->sta.capability[0] &= (~ZM_BIT_4);
            }

            /* authentication with open system */
            //zfStaStartConnect(dev, 0);
            wd->sta.bIsSharedKey = 0;
        }

        /* Improve WEP/TKIP performace with HT AP, detail information please look bug#32495 */
        /*
        if ( (pBssInfo->broadcomHTAp == 1)
             && (wd->sta.SWEncryptEnable != 0) )
        {
            zfHpSetTTSIFSTime(dev, 0xa);
        }
        else
        {
            zfHpSetTTSIFSTime(dev, 0x8);
        }
        */
    }
    else
    {
        zm_debug_msg0("Desired SSID not found");
        goto zlConnectFailed;
    }


    zfCoreSetFrequencyV2(dev, wd->frequency, zfStaStartConnectCb);
    return;

zlConnectFailed:
    zfStaConnectFail(dev, ZM_STATUS_MEDIA_DISCONNECT_NOT_FOUND, wd->sta.bssid, 0);
    return;
}