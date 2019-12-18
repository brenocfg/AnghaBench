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
typedef  int u8_t ;
struct zsBssList {int bssCount; struct zsBssInfo* head; } ;
struct zsBssInfo {struct zsBssInfo* next; } ;
struct TYPE_4__ {int bssCount; struct zsBssInfo* head; } ;
struct TYPE_5__ {TYPE_1__ bssList; } ;
struct TYPE_6__ {TYPE_2__ sta; } ;

/* Variables and functions */
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfMemoryCopy (int*,int*,int) ; 
 int /*<<< orphan*/  zfScanMgrScanAck (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zm_assert (int) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfiWlanQueryBssList(zdev_t* dev, struct zsBssList* pBssList)
{
    struct zsBssInfo*   pBssInfo;
    struct zsBssInfo*   pDstBssInfo;
    u8_t   i;
    u8_t*  pMemList;
    u8_t*  pMemInfo;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    pMemList = (u8_t*) pBssList;
    pMemInfo = pMemList + sizeof(struct zsBssList);
    pBssList->head = (struct zsBssInfo*) pMemInfo;

    zmw_enter_critical_section(dev);

    pBssInfo = wd->sta.bssList.head;
    pDstBssInfo = (struct zsBssInfo*) pMemInfo;
    pBssList->bssCount = wd->sta.bssList.bssCount;

    for( i=0; i<wd->sta.bssList.bssCount; i++ )
    {
        zfMemoryCopy((u8_t*)pDstBssInfo, (u8_t*)pBssInfo,
                sizeof(struct zsBssInfo));

        if ( pBssInfo->next != NULL )
        {
            pBssInfo = pBssInfo->next;
            pDstBssInfo->next = pDstBssInfo + 1;
            pDstBssInfo++;
        }
        else
        {
            zm_assert(i==(wd->sta.bssList.bssCount-1));
        }
    }

    zmw_leave_critical_section(dev);

    zfScanMgrScanAck(dev);
}