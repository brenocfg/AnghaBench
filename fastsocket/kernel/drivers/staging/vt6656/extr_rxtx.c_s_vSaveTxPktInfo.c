#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* WORD ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {TYPE_1__* abyTxPktInfo; } ;
struct TYPE_7__ {TYPE_2__ scStatistic; } ;
struct TYPE_5__ {int /*<<< orphan*/  abyDestAddr; void* wFIFOCtl; void* wLength; int /*<<< orphan*/  byBroadMultiUni; } ;
typedef  TYPE_2__* PSStatCounter ;
typedef  TYPE_3__* PSDevice ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  size_t BYTE ;

/* Variables and functions */
 scalar_t__ IS_BROADCAST_ADDRESS (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_MULTICAST_ADDRESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_PKT_BROAD ; 
 int /*<<< orphan*/  TX_PKT_MULTI ; 
 int /*<<< orphan*/  TX_PKT_UNI ; 
 int /*<<< orphan*/  U_ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
VOID
s_vSaveTxPktInfo(PSDevice pDevice, BYTE byPktNum, PBYTE pbyDestAddr, WORD wPktLength, WORD wFIFOCtl)
{
    PSStatCounter           pStatistic=&(pDevice->scStatistic);


    if (IS_BROADCAST_ADDRESS(pbyDestAddr))
        pStatistic->abyTxPktInfo[byPktNum].byBroadMultiUni = TX_PKT_BROAD;
    else if (IS_MULTICAST_ADDRESS(pbyDestAddr))
        pStatistic->abyTxPktInfo[byPktNum].byBroadMultiUni = TX_PKT_MULTI;
    else
        pStatistic->abyTxPktInfo[byPktNum].byBroadMultiUni = TX_PKT_UNI;

    pStatistic->abyTxPktInfo[byPktNum].wLength = wPktLength;
    pStatistic->abyTxPktInfo[byPktNum].wFIFOCtl = wFIFOCtl;
    memcpy(pStatistic->abyTxPktInfo[byPktNum].abyDestAddr, pbyDestAddr, U_ETHER_ADDR_LEN);
}