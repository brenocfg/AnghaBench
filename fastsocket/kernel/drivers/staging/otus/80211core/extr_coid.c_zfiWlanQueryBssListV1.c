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
typedef  int u8_t ;
struct zsBssListV1 {int bssCount; TYPE_1__* bssInfo; } ;
struct zsBssInfo {int* bssid; scalar_t__* ssid; scalar_t__ frequency; struct zsBssInfo* next; } ;
struct TYPE_6__ {int bssCount; struct zsBssInfo* head; } ;
struct TYPE_7__ {scalar_t__ ssidLen; int* ssid; TYPE_2__ bssList; int /*<<< orphan*/  bssid; } ;
struct TYPE_8__ {scalar_t__ wlanMode; scalar_t__ frequency; TYPE_3__ sta; } ;
struct TYPE_5__ {int* ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_MAC_WORD_TO_BYTE (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ ZM_MODE_INFRASTRUCTURE ; 
 TYPE_4__* wd ; 
 int /*<<< orphan*/  zfMemoryCopy (int*,int*,int) ; 
 int /*<<< orphan*/  zfScanMgrScanAck (int /*<<< orphan*/ *) ; 
 scalar_t__ zfStaIsConnected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_assert (int) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfiWlanQueryBssListV1(zdev_t* dev, struct zsBssListV1* bssListV1)
{
    struct zsBssInfo*   pBssInfo;
    //struct zsBssInfo*   pDstBssInfo;
    u8_t   i, j, bdrop = 0, k = 0, Same_Count = 0;
    u8_t   bssid[6];
    //u8_t*  pMemList;
    //u8_t*  pMemInfo;
    zmw_get_wlan_dev(dev);
    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);

    bssListV1->bssCount = wd->sta.bssList.bssCount;

    pBssInfo = wd->sta.bssList.head;
    ZM_MAC_WORD_TO_BYTE(wd->sta.bssid, bssid);

    for( i=0; i<wd->sta.bssList.bssCount; i++ )
    {
        bdrop = 0;
        if ( zfStaIsConnected(dev)
             && (wd->wlanMode == ZM_MODE_INFRASTRUCTURE ) )
        {
			for (j = 0; j < 6; j++)
            {
                if ( pBssInfo->bssid[j] != bssid[j] )
                {
                    break;
                }
            }

            if  ( (j == 6)
                  &&((pBssInfo->ssid[1] == wd->sta.ssidLen) || (pBssInfo->ssid[1] == 0) )&& (pBssInfo->frequency == wd->frequency) )
            {
				if(pBssInfo->ssid[1] == 0)
					pBssInfo->ssid[1] = wd->sta.ssidLen;

				if(Same_Count == 0)
				{//First meet
					Same_Count++;
				}
				else
				{//same one
					bdrop = 1;
					bssListV1->bssCount--;
				}

            }
        }

        if (bdrop == 0)
        {
            zfMemoryCopy((u8_t*)(&bssListV1->bssInfo[k]), (u8_t*)pBssInfo,
                sizeof(struct zsBssInfo));

			if(Same_Count == 1)
			{
				zfMemoryCopy(&(bssListV1->bssInfo[k].ssid[2]), wd->sta.ssid, wd->sta.ssidLen);
				Same_Count++;
			}

			k++;
        }

        if ( pBssInfo->next != NULL )
        {
            pBssInfo = pBssInfo->next;
        }
        else
        {
            zm_assert(i==(wd->sta.bssList.bssCount-1));
        }
    }

    zmw_leave_critical_section(dev);

    zfScanMgrScanAck(dev);
}