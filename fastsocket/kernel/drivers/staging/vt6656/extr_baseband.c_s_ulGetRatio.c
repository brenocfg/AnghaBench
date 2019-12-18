#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_3__ {int* aulPktNum; int uDiversityCnt; } ;
typedef  TYPE_1__* PSDevice ;

/* Variables and functions */
 int RATE_1M ; 
 int RATE_48M ; 
 size_t RATE_54M ; 
 scalar_t__ TOP_RATE_48M ; 
 scalar_t__ TOP_RATE_54M ; 

__attribute__((used)) static
ULONG
s_ulGetRatio (PSDevice pDevice)
{
int     ii,jj;
ULONG   ulRatio = 0;
ULONG   ulMaxPacket;
ULONG   ulPacketNum;

    //This is a thousand-ratio
    ulMaxPacket = pDevice->aulPktNum[RATE_54M];
    if ( pDevice->aulPktNum[RATE_54M] != 0 ) {
        ulPacketNum = pDevice->aulPktNum[RATE_54M];
        ulRatio = (ulPacketNum * 1000 / pDevice->uDiversityCnt);
        ulRatio += TOP_RATE_54M;
    }
    for ( ii=RATE_48M;ii>=RATE_1M;ii-- ) {
        if ( pDevice->aulPktNum[ii] > ulMaxPacket ) {
            ulPacketNum = 0;
            for ( jj=RATE_54M;jj>=ii;jj--)
                ulPacketNum += pDevice->aulPktNum[jj];
            ulRatio = (ulPacketNum * 1000 / pDevice->uDiversityCnt);
            ulRatio += TOP_RATE_48M;
            ulMaxPacket = pDevice->aulPktNum[ii];
        }

    }

    return ulRatio;
}