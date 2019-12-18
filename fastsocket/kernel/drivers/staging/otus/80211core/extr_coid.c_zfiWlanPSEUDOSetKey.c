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
typedef  int /*<<< orphan*/  u32_t ;
typedef  int u16_t ;
struct zsKeyInfo {int keyLength; int flag; int /*<<< orphan*/ * key; scalar_t__ macAddr; } ;
struct TYPE_3__ {int* txiv; void* encryMode; } ;
struct TYPE_4__ {TYPE_1__ sta; } ;

/* Variables and functions */
 void* ZM_AES ; 
 void* ZM_CENC ; 
 int ZM_KEY_FLAG_CENC ; 
 void* ZM_NO_WEP ; 
 int /*<<< orphan*/  ZM_STATUS_SUCCESS ; 
 void* ZM_TKIP ; 
 void* ZM_WEP128 ; 
 void* ZM_WEP256 ; 
 void* ZM_WEP64 ; 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfCoreSetKey (int /*<<< orphan*/ *,int,int,void*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

u8_t zfiWlanPSEUDOSetKey(zdev_t* dev, struct zsKeyInfo keyInfo)
{
    //u16_t  broadcast[3] = {0xffff, 0xffff, 0xffff};
    //u32_t* key;
    u8_t   micKey[16];

    zmw_get_wlan_dev(dev);

    switch (keyInfo.keyLength)
    {
        case 5:
            wd->sta.encryMode = ZM_WEP64;
            /* use default key */
            zfCoreSetKey(dev, 64, 0, ZM_WEP64, (u16_t *)keyInfo.macAddr, (u32_t*) keyInfo.key);
		          break;

       	case 13:
            wd->sta.encryMode = ZM_WEP128;
            /* use default key */
            zfCoreSetKey(dev, 64, 0, ZM_WEP128, (u16_t *)keyInfo.macAddr, (u32_t*) keyInfo.key);
          		break;

       	case 29:
            wd->sta.encryMode = ZM_WEP256;
            /* use default key */
            zfCoreSetKey(dev, 64, 1, ZM_WEP256,  (u16_t *)keyInfo.macAddr, (u32_t*) (&keyInfo.key[16]));
            zfCoreSetKey(dev, 64, 0, ZM_WEP256, (u16_t *)keyInfo.macAddr, (u32_t*) keyInfo.key);
		          break;

       	case 16:
            wd->sta.encryMode = ZM_AES;
            //zfCoreSetKey(dev, 0, 0, ZM_AES, (u16_t *)keyInfo.macAddr, (u32_t*) keyInfo.key);
            zfCoreSetKey(dev, 64, 0, ZM_AES, (u16_t *)keyInfo.macAddr, (u32_t*) keyInfo.key);
            break;

       	case 32:
#ifdef ZM_ENABLE_CENC
            if (keyInfo.flag & ZM_KEY_FLAG_CENC)
            {
                u16_t boardcastAddr[3] = {0xffff, 0xffff, 0xffff};
                u16_t Addr_a[] = { 0x0000, 0x0080, 0x0901};
                u16_t Addr_b[] = { 0x0000, 0x0080, 0x0902};
                /* CENC test: user0,1 and user2 for boardcast */
                wd->sta.encryMode = ZM_CENC;
                zfCoreSetKey(dev, 0, 1, ZM_CENC, (u16_t *)Addr_a, (u32_t*) (&keyInfo.key[16]));
                zfCoreSetKey(dev, 0, 0, ZM_CENC, (u16_t *)Addr_a, (u32_t*) keyInfo.key);

                zfCoreSetKey(dev, 1, 1, ZM_CENC, (u16_t *)Addr_b, (u32_t*) (&keyInfo.key[16]));
                zfCoreSetKey(dev, 1, 0, ZM_CENC, (u16_t *)Addr_b, (u32_t*) keyInfo.key);

                zfCoreSetKey(dev, 2, 1, ZM_CENC, (u16_t *)boardcastAddr, (u32_t*) (&keyInfo.key[16]));
                zfCoreSetKey(dev, 2, 0, ZM_CENC, (u16_t *)boardcastAddr, (u32_t*) keyInfo.key);

                /* Initialize PN sequence */
                wd->sta.txiv[0] = 0x5c365c36;
                wd->sta.txiv[1] = 0x5c365c36;
                wd->sta.txiv[2] = 0x5c365c36;
                wd->sta.txiv[3] = 0x5c365c36;
            }
            else
#endif //ZM_ENABLE_CENC
            {
                wd->sta.encryMode = ZM_TKIP;
                zfCoreSetKey(dev, 64, 1, ZM_TKIP, (u16_t *)keyInfo.macAddr, (u32_t*) micKey);
                zfCoreSetKey(dev, 64, 0, ZM_TKIP, (u16_t *)keyInfo.macAddr, (u32_t*) keyInfo.key);
            }
            break;
        default:
            wd->sta.encryMode = ZM_NO_WEP;
    }

    return ZM_STATUS_SUCCESS;
}