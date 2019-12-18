#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  size_t u8_t ;
typedef  int /*<<< orphan*/  u32_t ;
typedef  int u16_t ;
struct zsKeyInfo {int flag; int keyLength; size_t keyIndex; size_t vapId; int /*<<< orphan*/ * key; int /*<<< orphan*/  initIv; scalar_t__ macAddr; } ;
struct TYPE_12__ {size_t encryMode; } ;
struct TYPE_13__ {scalar_t__ iv32; scalar_t__ iv16; scalar_t__ tk; } ;
struct TYPE_11__ {int ibssWpa2Psk; int* bssid; size_t encryMode; int* txiv; int* rxiv; size_t cencKeyId; int keyId; scalar_t__ wpaState; int* rxivGK; size_t** wepKey; size_t* SWEncryMode; scalar_t__ iv32; scalar_t__ iv16; int /*<<< orphan*/ * rxMicKey; TYPE_6__* rxSeed; TYPE_2__* oppositeInfo; int /*<<< orphan*/  txMicKey; TYPE_6__ txSeed; } ;
struct TYPE_10__ {int** txiv; int* capab; size_t* encryMode; size_t* bcKeyIndex; size_t* bcHalKeyIdx; int /*<<< orphan*/ * bcMicKey; scalar_t__* iv32; scalar_t__* iv16; TYPE_1__* staTable; } ;
struct TYPE_14__ {int TKIP_Group_KeyChanging; TYPE_5__ ws; TYPE_4__ sta; TYPE_3__ ap; scalar_t__ macAddr; } ;
struct TYPE_9__ {int camIdx; int pkInstalled; size_t encryMode; scalar_t__ wpaState; scalar_t__ iv32; scalar_t__ iv16; } ;
struct TYPE_8__ {size_t encryMode; int* txiv; int* rxiv; size_t cencKeyIdx; int keyIdx; int /*<<< orphan*/  rxMicKey; int /*<<< orphan*/  txMicKey; scalar_t__ iv32; scalar_t__ iv16; } ;

/* Variables and functions */
 size_t ZM_AES ; 
 void* ZM_CENC ; 
 int /*<<< orphan*/  ZM_EVENT_SKIP_COUNTERMEASURE ; 
 int ZM_KEY_FLAG_AUTHENTICATOR ; 
 int ZM_KEY_FLAG_CENC ; 
 int ZM_KEY_FLAG_DEFAULT_KEY ; 
 int ZM_KEY_FLAG_GK ; 
 int ZM_KEY_FLAG_INIT_IV ; 
 int ZM_KEY_FLAG_PK ; 
 size_t ZM_NO_WEP ; 
 size_t ZM_STATUS_FAILURE ; 
 size_t ZM_STATUS_SUCCESS ; 
 void* ZM_STA_WPA_STATE_GK_OK ; 
 scalar_t__ ZM_STA_WPA_STATE_INIT ; 
 scalar_t__ ZM_STA_WPA_STATE_PK_OK ; 
 size_t ZM_TKIP ; 
 size_t ZM_USER_KEY_GK ; 
 size_t ZM_USER_KEY_PK ; 
 size_t ZM_WEP128 ; 
 size_t ZM_WEP256 ; 
 size_t ZM_WEP64 ; 
 TYPE_7__* wd ; 
 int /*<<< orphan*/  zfApClearStaKey (int /*<<< orphan*/ *,int*) ; 
 int zfApFindSta (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  zfHpSetApGroupKey (int /*<<< orphan*/ *,scalar_t__,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  zfHpSetApPairwiseKey (int /*<<< orphan*/ *,int*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfHpSetDefaultKey (int /*<<< orphan*/ *,size_t,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfHpSetPerUserKey (int /*<<< orphan*/ *,size_t,size_t,size_t*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfMemoryCopy (size_t*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfMicSetKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t zfStaFindOppositeByMACAddr (int /*<<< orphan*/ *,int*,size_t*) ; 
 int /*<<< orphan*/  zfTimerCancel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfTimerSchedule (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfTkipInit (int /*<<< orphan*/ *,size_t*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zm_debug_msg2 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u8_t zfiWlanSetKey(zdev_t* dev, struct zsKeyInfo keyInfo)
{
    u16_t  broadcast[3] = {0xffff, 0xffff, 0xffff};
    u32_t* key;
    u8_t   encryMode = ZM_NO_WEP;
#ifdef ZM_ENABLE_IBSS_WPA2PSK
    u8_t   encryType = ZM_NO_WEP;
#endif
    u8_t   micKey[16];
    u16_t  id = 0;
    u8_t   vapId, i, addr[6];
    u8_t   userIdx=0;

#ifdef ZM_ENABLE_IBSS_WPA2PSK
    /* Determine opposite exist or not */
    u8_t   res, peerIdx;
//    u8_t   userIdx=0;

    zmw_get_wlan_dev(dev);

    if ( wd->sta.ibssWpa2Psk == 1 )
    {
        zmw_enter_critical_section(dev);
        res = zfStaFindOppositeByMACAddr(dev, (u16_t*)keyInfo.macAddr, &peerIdx);
        if( res == 0 )
        {
            userIdx = peerIdx;
            if ( wd->sta.oppositeInfo[userIdx].camIdx == 0xff )
                wd->sta.oppositeInfo[userIdx].camIdx = userIdx;
        }
        zmw_leave_critical_section(dev);
    }
#else
    zmw_get_wlan_dev(dev);
#endif

    if ( keyInfo.flag & ZM_KEY_FLAG_AUTHENTICATOR )
    {   /* set key by authenticator */
        /* set pairwise key */
        if (keyInfo.flag & ZM_KEY_FLAG_PK)
        {
            /* Find STA's information */
            if ((id = zfApFindSta(dev, keyInfo.macAddr)) == 0xffff)
            {
                /* Can't STA in the staTable */
                return ZM_STATUS_FAILURE;
            }

            wd->ap.staTable[id].iv16 = 0;
            wd->ap.staTable[id].iv32 = 0;

            if (keyInfo.keyLength == 32)
            {   /* TKIP */
                //u8_t KeyRsc[6] = {0, 0, 0, 0, 0, 0};

                /* In the current AP mode, we set KeyRsc to zero */
                //zfTkipInit(keyInfo.key, (u8_t*) wd->macAddr,
                //           &(wd->ap.staTable[id].txSeed), KeyRsc);
                //zfTkipInit(keyInfo.key, (u8_t*) keyInfo.macAddr,
                //           &(wd->ap.staTable[id].rxSeed), KeyRsc);
#ifdef ZM_ENABLE_CENC
                if (keyInfo.flag & ZM_KEY_FLAG_CENC)
                {
                    zm_debug_msg0("Set CENC pairwise Key");

                    wd->ap.staTable[id].encryMode = ZM_CENC;

                    /* Reset txiv and rxiv */
                    wd->ap.staTable[id].txiv[0] = 0x5c365c37;
                    wd->ap.staTable[id].txiv[1] = 0x5c365c36;
                    wd->ap.staTable[id].txiv[2] = 0x5c365c36;
                    wd->ap.staTable[id].txiv[3] = 0x5c365c36;

                    wd->ap.staTable[id].rxiv[0] = 0x5c365c36;
                    wd->ap.staTable[id].rxiv[1] = 0x5c365c36;
                    wd->ap.staTable[id].rxiv[2] = 0x5c365c36;
                    wd->ap.staTable[id].rxiv[3] = 0x5c365c36;

                    /* Set Key Index */
                    wd->ap.staTable[id].cencKeyIdx = keyInfo.keyIndex;

                    //zfCoreSetKey(dev, id+1, 1, ZM_CENC, (u16_t *)keyInfo.macAddr,
                    //          (u32_t*) &keyInfo.key[16]);
                }
                else
#endif //ZM_ENABLE_CENC
                {
                    wd->ap.staTable[id].encryMode = ZM_TKIP;

                    zfMemoryCopy(micKey, &keyInfo.key[16], 8);
                    zfMemoryCopy(&micKey[8], &keyInfo.key[24], 8);

                    //zfCoreSetKey(dev, id+1, 1, ZM_TKIP, (u16_t *)keyInfo.macAddr,
                    //           (u32_t*) micKey);

                    /* For fragmentation, we use software MIC */
                    zfMemoryCopy((u8_t *)&(wd->ap.staTable[id].txMicKey), &(keyInfo.key[16]), 8);
                    zfMemoryCopy((u8_t *)&(wd->ap.staTable[id].rxMicKey), &(keyInfo.key[24]), 8);

                }
            }
            else if (keyInfo.keyLength == 16)
            {   /* AES */
                wd->ap.staTable[id].encryMode = ZM_AES;
            }
            else if (keyInfo.keyLength == 0)
            {
                /* Clear Key Info */
                zfApClearStaKey(dev, (u16_t *)keyInfo.macAddr);

                return ZM_STATUS_SUCCESS;
            }
            else
            {
                return ZM_STATUS_FAILURE;
            }

            //zfCoreSetKey(dev, id+1, 0, wd->ap.staTable[id].encryMode,
            //      (u16_t *)keyInfo.macAddr, (u32_t*) keyInfo.key);
            zfHpSetApPairwiseKey(dev, (u16_t *)keyInfo.macAddr,
                    wd->ap.staTable[id].encryMode, (u32_t*) keyInfo.key,
                    (u32_t*) &keyInfo.key[16], id+1);
            wd->ap.staTable[id].keyIdx = id + 1 + 4;
        }
        else if (keyInfo.flag & ZM_KEY_FLAG_GK)
        {
            vapId = keyInfo.vapId;

            wd->ap.iv16[vapId] = 0;
            wd->ap.iv32[vapId] = 0;

            if (keyInfo.keyLength == 32)
            {   /* TKIP */
                //u8_t KeyRsc[6] = {0, 0, 0, 0, 0, 0};

                //zfTkipInit(keyInfo.key, (u8_t*) wd->macAddr,
                //           &(wd->ap.bcSeed), KeyRsc);
#ifdef ZM_ENABLE_CENC
                if (keyInfo.flag & ZM_KEY_FLAG_CENC)
                {
                    encryMode = ZM_CENC;
                    zm_debug_msg0("Set CENC group Key");

                    /* Reset txiv and rxiv */
                    wd->ap.txiv[vapId][0] = 0x5c365c36;
                    wd->ap.txiv[vapId][1] = 0x5c365c36;
                    wd->ap.txiv[vapId][2] = 0x5c365c36;
                    wd->ap.txiv[vapId][3] = 0x5c365c36;

                    //zfCoreSetKey(dev, 0, 1, ZM_CENC, keyInfo.vapAddr,
                    //          (u32_t*) &keyInfo.key[16]);
                    key = (u32_t*) keyInfo.key;
                }
                else
#endif //ZM_ENABLE_CENC
                {
                    encryMode = ZM_TKIP;
                    key = (u32_t *)keyInfo.key;

                    /* set MIC key to HMAC */
                    //zfCoreSetKey(dev, 0, 1, ZM_TKIP, broadcast,
                    //         (u32_t*) (&keyInfo.key[16]));
                    //zfCoreSetKey(dev, 0, 1, ZM_TKIP, keyInfo.vapAddr,
                    //           (u32_t*) (&keyInfo.key[16]));

                    zfMicSetKey(&(keyInfo.key[16]), &(wd->ap.bcMicKey[0]));
                    key = (u32_t*) keyInfo.key;
                }
            }
            else if (keyInfo.keyLength == 16)
            {   /* AES */
                encryMode = ZM_AES;
                key = (u32_t *)keyInfo.key;
                zm_debug_msg0("CWY - Set AES Group Key");
            }
            else if (keyInfo.keyLength == 0)
            {
                /* Clear Key Info */
                zfApClearStaKey(dev, broadcast);

                /* Turn off WEP bit in the capability field */
                wd->ap.capab[vapId] &= 0xffef;

                return ZM_STATUS_SUCCESS;
            }
            else
            {   /* WEP */
                if (keyInfo.keyLength == 5)
                {
                    encryMode = ZM_WEP64;
                }
                else if (keyInfo.keyLength == 13)
                {
                    encryMode = ZM_WEP128;
                }
                else if (keyInfo.keyLength == 29)
                {
                    encryMode = ZM_WEP256;
                }

                key = (u32_t*) keyInfo.key;
            }

            // Modification for CAM not support VAP search
            //zfCoreSetKey(dev, 0, 0, encryMode, broadcast, key);
            //zfCoreSetKey(dev, 0, 0, encryMode, wd->macAddr, key);
            //zfCoreSetKey(dev, 0, 0, encryMode, keyInfo.vapAddr, key);
            zfHpSetApGroupKey(dev, wd->macAddr, encryMode,
                    key, (u32_t*) &keyInfo.key[16], vapId);

            //zfiWlanSetEncryMode(dev, encryMode);
            wd->ws.encryMode = encryMode;

            /* set the multicast address encryption type */
            wd->ap.encryMode[vapId] = encryMode;

            /* set the multicast key index */
            wd->ap.bcKeyIndex[vapId] = keyInfo.keyIndex;
            wd->ap.bcHalKeyIdx[vapId] = vapId + 60;

            /* Turn on WEP bit in the capability field */
            wd->ap.capab[vapId] |= 0x10;
        }
    }
    else
    {   /* set by supplicant */

        if ( keyInfo.flag & ZM_KEY_FLAG_PK )
        {   /* set pairwise key */

            //zfTkipInit(keyInfo.key, (u8_t*) wd->macAddr,
            //           &wd->sta.txSeed, keyInfo.initIv);
            //zfTkipInit(keyInfo.key, (u8_t*) wd->sta.bssid,
            //           &wd->sta.rxSeed[keyInfo.keyIndex], keyInfo.initIv);

#ifdef ZM_ENABLE_IBSS_WPA2PSK
            if ( wd->sta.ibssWpa2Psk == 1 )
            {
                /* unicast -- > pairwise key */
                wd->sta.oppositeInfo[userIdx].iv16 = 0;
                wd->sta.oppositeInfo[userIdx].iv32 = 0;
            }
            else
            {
                wd->sta.iv16 = 0;
                wd->sta.iv32 = 0;
            }

            wd->sta.oppositeInfo[userIdx].pkInstalled = 1;
#else
            wd->sta.iv16 = 0;
            wd->sta.iv32 = 0;

            wd->sta.oppositeInfo[userIdx].pkInstalled = 1;
#endif

            if ( keyInfo.keyLength == 32 )
            {   /* TKIP */
                zfTkipInit(keyInfo.key, (u8_t*) wd->macAddr,
                        &wd->sta.txSeed, keyInfo.initIv);
                zfTkipInit(keyInfo.key, (u8_t*) wd->sta.bssid,
                        &wd->sta.rxSeed[keyInfo.keyIndex], keyInfo.initIv);

#ifdef ZM_ENABLE_CENC
                if (keyInfo.flag & ZM_KEY_FLAG_CENC)
                {
                    zm_debug_msg0("Set CENC pairwise Key");

                    wd->sta.encryMode = ZM_CENC;

                    /* Reset txiv and rxiv */
                    wd->sta.txiv[0] = 0x5c365c36;
                    wd->sta.txiv[1] = 0x5c365c36;
                    wd->sta.txiv[2] = 0x5c365c36;
                    wd->sta.txiv[3] = 0x5c365c36;

                    wd->sta.rxiv[0] = 0x5c365c37;
                    wd->sta.rxiv[1] = 0x5c365c36;
                    wd->sta.rxiv[2] = 0x5c365c36;
                    wd->sta.rxiv[3] = 0x5c365c36;

                    /* Set Key Index */
                    wd->sta.cencKeyId = keyInfo.keyIndex;

                    //zfCoreSetKey(dev, id+1, 1, ZM_CENC, (u16_t *)keyInfo.macAddr,
                    //         (u32_t*) &keyInfo.key[16]);
                }
                else
#endif //ZM_ENABLE_CENC
                {
                    wd->sta.encryMode = ZM_TKIP;

                    //zfCoreSetKey(dev, 0, 1, ZM_TKIP, wd->sta.bssid,
                    //         (u32_t*) &keyInfo.key[16]);

                    zfMicSetKey(&keyInfo.key[16], &wd->sta.txMicKey);
                    zfMicSetKey(&keyInfo.key[24],
                                &wd->sta.rxMicKey[keyInfo.keyIndex]);
                }
            }
            else if ( keyInfo.keyLength == 16 )
            {   /* AES */
#ifdef ZM_ENABLE_IBSS_WPA2PSK
                if ( wd->sta.ibssWpa2Psk == 1 )
                {
                    wd->sta.oppositeInfo[userIdx].encryMode = ZM_AES;
                    encryType = wd->sta.oppositeInfo[userIdx].encryMode;
                }
                else
                {
                    wd->sta.encryMode = ZM_AES;
                    encryType = wd->sta.encryMode;
                }
#else
                wd->sta.encryMode = ZM_AES;
#endif
            }
            else
            {
                return ZM_STATUS_FAILURE;
            }

            /* user 0 */
            //zfCoreSetKey(dev, 0, 0, wd->sta.encryMode,
            //         wd->sta.bssid, (u32_t*) keyInfo.key);
            //zfHpSetStaPairwiseKey(dev, wd->sta.bssid, wd->sta.encryMode,
            //    (u32_t*) keyInfo.key, (u32_t*) &keyInfo.key[16]);

#ifdef ZM_ENABLE_IBSS_WPA2PSK
            if ( (keyInfo.keyLength==16) && (wd->sta.ibssWpa2Psk==1) )
            { /* If not AES-CCMP and ibss network , use traditional */
                zfHpSetPerUserKey(dev,
                                userIdx,
                                keyInfo.keyIndex,  // key id == 0 ( Pairwise key = 0 )
                                (u8_t*)keyInfo.macAddr,   // RX need Source Address ( Address 2 )
                                encryType,
//                              wd->sta.encryMode,
                                (u32_t*) keyInfo.key, (u32_t*) &keyInfo.key[16]);

                wd->sta.oppositeInfo[userIdx].wpaState = ZM_STA_WPA_STATE_PK_OK ;
            }
            else
            {/* Big Endian and Little Endian Compatibility */
                for (i = 0; i < 3; i++)
                {
                    addr[2 * i] = wd->sta.bssid[i] & 0xff;
                    addr[2 * i + 1] = wd->sta.bssid[i] >> 8;
                }
                zfHpSetPerUserKey(dev,
                                    ZM_USER_KEY_PK,   // user id
                                    0,                // key id
                                    addr,//(u8_t *)wd->sta.bssid,
                              wd->sta.encryMode,
                              (u32_t*) keyInfo.key, (u32_t*) &keyInfo.key[16]);

                wd->sta.keyId = 4;
            }
#else
            /* Big Endian and Little Endian Compatibility */
            for (i = 0; i < 3; i++)
            {
                addr[2 * i] = wd->sta.bssid[i] & 0xff;
                addr[2 * i + 1] = wd->sta.bssid[i] >> 8;
            }
            zfHpSetPerUserKey(dev,
                              ZM_USER_KEY_PK,   // user id
                              0,                // key id
                              addr,//(u8_t *)wd->sta.bssid,
                              wd->sta.encryMode,
                              (u32_t*) keyInfo.key, (u32_t*) &keyInfo.key[16]);

            wd->sta.keyId = 4;
#endif

            wd->sta.wpaState = ZM_STA_WPA_STATE_PK_OK;
        }
        else if ( keyInfo.flag & ZM_KEY_FLAG_GK )
        {   /* set group key */

            zfTkipInit(keyInfo.key, (u8_t*) wd->sta.bssid,
                       &wd->sta.rxSeed[keyInfo.keyIndex], keyInfo.initIv);

            if ( keyInfo.keyLength == 32 )
            {   /* TKIP */
#ifdef ZM_ENABLE_CENC
                if (keyInfo.flag & ZM_KEY_FLAG_CENC)
                {
                    encryMode = ZM_CENC;
                    zm_debug_msg0("Set CENC group Key");

                    /* Reset txiv and rxiv */
                    wd->sta.rxivGK[0] = 0x5c365c36;
                    wd->sta.rxivGK[1] = 0x5c365c36;
                    wd->sta.rxivGK[2] = 0x5c365c36;
                    wd->sta.rxivGK[3] = 0x5c365c36;

                    //zfCoreSetKey(dev, 0, 1, ZM_CENC, keyInfo.vapAddr,
                    //         (u32_t*) &keyInfo.key[16]);
                    key = (u32_t*) keyInfo.key;
                }
                else
#endif //ZM_ENABLE_CENC
                {
                    encryMode = ZM_TKIP;
                    key = (u32_t*) wd->sta.rxSeed[keyInfo.keyIndex].tk;

                    if ( !(keyInfo.flag & ZM_KEY_FLAG_INIT_IV) )
                    {
                        wd->sta.rxSeed[keyInfo.keyIndex].iv16 = 0;
                        wd->sta.rxSeed[keyInfo.keyIndex].iv32 = 0;
                    }

                    /* set MIC key to HMAC */
                    //zfCoreSetKey(dev, 8, 1, ZM_TKIP, broadcast,
                    //         (u32_t*) (&keyInfo.key[16]));

                    zfMicSetKey(&keyInfo.key[24],
                                &wd->sta.rxMicKey[keyInfo.keyIndex]);
                }
            }
            else if ( keyInfo.keyLength == 16 )
            {   /* AES */
                encryMode = ZM_AES;
                //key = (u32_t*) wd->sta.rxSeed[keyInfo.keyIndex].tk;
            }
            else
            {   /* WEP */
                if ( keyInfo.keyLength == 5 )
                {
                    encryMode = ZM_WEP64;
                }
                else if ( keyInfo.keyLength == 13 )
                {
                    encryMode = ZM_WEP128;
                }
                else if ( keyInfo.keyLength == 29 )
                {
                    encryMode = ZM_WEP256;
                }

                key = (u32_t*) keyInfo.key;
            }

            /* user 8 */
            //zfCoreSetKey(dev, 8, 0, encryMode, broadcast, key);
            //zfHpSetStaGroupKey(dev, broadcast, encryMode,
            //        (u32_t*) keyInfo.key, (u32_t*) (&keyInfo.key[16]));

#ifdef ZM_ENABLE_IBSS_WPA2PSK
            if ( (keyInfo.keyLength==16) && (wd->sta.ibssWpa2Psk==1) )
            {/* If not AES-CCMP and ibss network , use traditional */
                zfHpSetPerUserKey(dev,
                              userIdx,
                              keyInfo.keyIndex,                // key id
                              // (u8_t *)broadcast,                  // for only 2 stations IBSS netwrl ( A2 )
                              (u8_t*)keyInfo.macAddr,   // for multiple ( > 2 ) stations IBSS network ( A2 )
                              encryMode,
                              (u32_t*) keyInfo.key, (u32_t*) &keyInfo.key[16]);
            }
            else
            {
                zfHpSetPerUserKey(dev,
                                ZM_USER_KEY_GK,   // user id
                                0,                // key id
                                (u8_t *)broadcast,
                                encryMode,
                                (u32_t*) keyInfo.key, (u32_t*) &keyInfo.key[16]);

                wd->sta.wpaState = ZM_STA_WPA_STATE_GK_OK;
            }
#else
            zfHpSetPerUserKey(dev,
                              ZM_USER_KEY_GK,   // user id
                              0,                // key id
                              (u8_t *)broadcast,
                              encryMode,
                              (u32_t*) keyInfo.key, (u32_t*) &keyInfo.key[16]);

            wd->sta.wpaState = ZM_STA_WPA_STATE_GK_OK;
#endif
        }
        else
        {   /* legacy WEP */
            zm_debug_msg0("legacy WEP");

            if ( keyInfo.keyIndex >= 4 )
            {
                return ZM_STATUS_FAILURE;
            }

            if ( keyInfo.keyLength == 5 )
            {
                zm_debug_msg0("WEP 64");

                encryMode = ZM_WEP64;
            }
            else if ( keyInfo.keyLength == 13 )
            {
                zm_debug_msg0("WEP 128");

                encryMode = ZM_WEP128;
            }
            else if ( keyInfo.keyLength == 32 )
            {
                /* TKIP */
                #if 0
                // Don't reset the IV since some AP would fail in IV check and drop our connection
                if ( wd->sta.wpaState != ZM_STA_WPA_STATE_PK_OK )
                {
                    wd->sta.iv16 = 0;
                    wd->sta.iv32 = 0;
                }
                #endif

                encryMode = ZM_TKIP;

                zfTkipInit(keyInfo.key, (u8_t*) wd->sta.bssid,
                           &wd->sta.rxSeed[keyInfo.keyIndex], keyInfo.initIv);
                zfMicSetKey(&keyInfo.key[24],
                           &wd->sta.rxMicKey[keyInfo.keyIndex]);
            }
            else if ( keyInfo.keyLength == 16 )
            {
                /* AES */
                #if 0
                // Don't reset the IV since some AP would fail in IV check and drop our connection
                if ( wd->sta.wpaState != ZM_STA_WPA_STATE_PK_OK )
                {
                    /* broadcast -- > group key */
                    /* Only initialize when set our default key ! */
                    wd->sta.iv16 = 0;
                    wd->sta.iv32 = 0;
                }
                #endif

                encryMode = ZM_AES;
            }
            else if ( keyInfo.keyLength == 29 )
            {
                zm_debug_msg0("WEP 256");

                encryMode = ZM_WEP256;
                //zfCoreSetKey(dev, 64, 1, wd->sta.encryMode,
                //         wd->sta.bssid, (u32_t*) (&keyInfo.key[16]));
            }
            else
            {
                return ZM_STATUS_FAILURE;
            }

            {
                u8_t i;

                zm_debug_msg0("key = ");
                for(i = 0; i < keyInfo.keyLength; i++)
                {
                    zm_debug_msg2("", keyInfo.key[i]);
                }
            }

            if ( keyInfo.flag & ZM_KEY_FLAG_DEFAULT_KEY )
            {
                //for WEP default key 1~3 and ATOM platform--CWYang(+)
                vapId = 0;
                wd->ap.bcHalKeyIdx[vapId] = keyInfo.keyIndex;
                wd->ap.bcKeyIndex[vapId] = keyInfo.keyIndex;
                wd->sta.keyId = keyInfo.keyIndex;
            }

			if(encryMode == ZM_TKIP)
			{
				if(wd->TKIP_Group_KeyChanging == 0x1)
				{
					zm_debug_msg0("Countermeasure : Cancel Old Timer ");
					zfTimerCancel(dev,	ZM_EVENT_SKIP_COUNTERMEASURE);
				}
				else
				{
					zm_debug_msg0("Countermeasure : Create New Timer ");
				}

				wd->TKIP_Group_KeyChanging = 0x1;
				zfTimerSchedule(dev, ZM_EVENT_SKIP_COUNTERMEASURE, 150);
			}



			//------------------------------------------------------------------------

            /* use default key */
            //zfCoreSetKey(dev, ZM_USER_KEY_DEFAULT+keyInfo.keyIndex, 0,
            //         wd->sta.encryMode, wd->sta.bssid, (u32_t*) keyInfo.key);

            if ( encryMode == ZM_TKIP ||
                 encryMode == ZM_AES )
            {
                zfHpSetDefaultKey(dev, keyInfo.keyIndex, encryMode,
                                 (u32_t*) keyInfo.key, (u32_t*) &keyInfo.key[16]);

#ifdef ZM_ENABLE_IBSS_WPA2PSK
            if ( (keyInfo.keyLength==16) && (wd->sta.ibssWpa2Psk==1) )
            {/* If not AES-CCMP and ibss network , use traditional */
                wd->sta.wpaState = ZM_STA_WPA_STATE_PK_OK;
            }
            else
            {
                if (wd->sta.wpaState == ZM_STA_WPA_STATE_PK_OK)
                    wd->sta.wpaState = ZM_STA_WPA_STATE_GK_OK;
                else
                {
                    wd->sta.wpaState = ZM_STA_WPA_STATE_PK_OK;
                    wd->sta.encryMode = encryMode;
                    wd->ws.encryMode = encryMode;
                }
            }
#else
                if (wd->sta.wpaState == ZM_STA_WPA_STATE_PK_OK)
                    wd->sta.wpaState = ZM_STA_WPA_STATE_GK_OK;
                else if ( wd->sta.wpaState == ZM_STA_WPA_STATE_INIT )
                {
                    wd->sta.wpaState = ZM_STA_WPA_STATE_PK_OK;
                    wd->sta.encryMode = encryMode;
                    wd->ws.encryMode = encryMode;
                }
#endif
            }
            else
            {
                zfHpSetDefaultKey(dev, keyInfo.keyIndex, encryMode,
                               (u32_t*) keyInfo.key, NULL);

                /* Save key for software WEP */
                zfMemoryCopy(wd->sta.wepKey[keyInfo.keyIndex], keyInfo.key,
                        keyInfo.keyLength);

                /* TODO: Check whether we need to save the SWEncryMode */
                wd->sta.SWEncryMode[keyInfo.keyIndex] = encryMode;

                wd->sta.encryMode = encryMode;
                wd->ws.encryMode = encryMode;
            }
        }
    }

//    wd->sta.flagKeyChanging = 1;
    return ZM_STATUS_SUCCESS;
}