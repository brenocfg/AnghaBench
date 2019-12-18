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
struct TYPE_3__ {int* uNumSQ3; int uDiversityCnt; } ;
typedef  TYPE_1__* PSDevice ;

/* Variables and functions */
 size_t RATE_11M ; 
 size_t RATE_12M ; 
 size_t RATE_18M ; 
 size_t RATE_1M ; 
 size_t RATE_24M ; 
 size_t RATE_2M ; 
 size_t RATE_36M ; 
 size_t RATE_48M ; 
 size_t RATE_54M ; 
 size_t RATE_5M ; 
 size_t RATE_6M ; 
 size_t RATE_9M ; 
 scalar_t__ TOP_RATE_11M ; 
 scalar_t__ TOP_RATE_12M ; 
 scalar_t__ TOP_RATE_18M ; 
 scalar_t__ TOP_RATE_1M ; 
 scalar_t__ TOP_RATE_24M ; 
 scalar_t__ TOP_RATE_2M ; 
 scalar_t__ TOP_RATE_36M ; 
 scalar_t__ TOP_RATE_48M ; 
 scalar_t__ TOP_RATE_54M ; 
 scalar_t__ TOP_RATE_55M ; 
 scalar_t__ TOP_RATE_6M ; 
 scalar_t__ TOP_RATE_9M ; 

__attribute__((used)) static
ULONG
s_ulGetRatio (PSDevice pDevice)
{
ULONG   ulRatio = 0;
ULONG   ulMaxPacket;
ULONG   ulPacketNum;

    //This is a thousand-ratio
    ulMaxPacket = pDevice->uNumSQ3[RATE_54M];
    if ( pDevice->uNumSQ3[RATE_54M] != 0 ) {
        ulPacketNum = pDevice->uNumSQ3[RATE_54M];
        ulRatio = (ulPacketNum * 1000 / pDevice->uDiversityCnt);
        //ulRatio = (pDevice->uNumSQ3[RATE_54M] * 1000 / pDevice->uDiversityCnt);
        ulRatio += TOP_RATE_54M;
    }
    if ( pDevice->uNumSQ3[RATE_48M] > ulMaxPacket ) {
        ulPacketNum = pDevice->uNumSQ3[RATE_54M] + pDevice->uNumSQ3[RATE_48M];
        ulRatio = (ulPacketNum * 1000 / pDevice->uDiversityCnt);
        //ulRatio = (pDevice->uNumSQ3[RATE_48M] * 1000 / pDevice->uDiversityCnt);
        ulRatio += TOP_RATE_48M;
        ulMaxPacket = pDevice->uNumSQ3[RATE_48M];
    }
    if ( pDevice->uNumSQ3[RATE_36M] > ulMaxPacket ) {
        ulPacketNum = pDevice->uNumSQ3[RATE_54M] + pDevice->uNumSQ3[RATE_48M] +
                      pDevice->uNumSQ3[RATE_36M];
        ulRatio = (ulPacketNum * 1000 / pDevice->uDiversityCnt);
        //ulRatio = (pDevice->uNumSQ3[RATE_36M] * 1000 / pDevice->uDiversityCnt);
        ulRatio += TOP_RATE_36M;
        ulMaxPacket = pDevice->uNumSQ3[RATE_36M];
    }
    if ( pDevice->uNumSQ3[RATE_24M] > ulMaxPacket ) {
        ulPacketNum = pDevice->uNumSQ3[RATE_54M] + pDevice->uNumSQ3[RATE_48M] +
                      pDevice->uNumSQ3[RATE_36M] + pDevice->uNumSQ3[RATE_24M];
        ulRatio = (ulPacketNum * 1000 / pDevice->uDiversityCnt);
        //ulRatio = (pDevice->uNumSQ3[RATE_24M] * 1000 / pDevice->uDiversityCnt);
        ulRatio += TOP_RATE_24M;
        ulMaxPacket = pDevice->uNumSQ3[RATE_24M];
    }
    if ( pDevice->uNumSQ3[RATE_18M] > ulMaxPacket ) {
        ulPacketNum = pDevice->uNumSQ3[RATE_54M] + pDevice->uNumSQ3[RATE_48M] +
                      pDevice->uNumSQ3[RATE_36M] + pDevice->uNumSQ3[RATE_24M] +
                      pDevice->uNumSQ3[RATE_18M];
        ulRatio = (ulPacketNum * 1000 / pDevice->uDiversityCnt);
        //ulRatio = (pDevice->uNumSQ3[RATE_18M] * 1000 / pDevice->uDiversityCnt);
        ulRatio += TOP_RATE_18M;
        ulMaxPacket = pDevice->uNumSQ3[RATE_18M];
    }
    if ( pDevice->uNumSQ3[RATE_12M] > ulMaxPacket ) {
        ulPacketNum = pDevice->uNumSQ3[RATE_54M] + pDevice->uNumSQ3[RATE_48M] +
                      pDevice->uNumSQ3[RATE_36M] + pDevice->uNumSQ3[RATE_24M] +
                      pDevice->uNumSQ3[RATE_18M] + pDevice->uNumSQ3[RATE_12M];
        ulRatio = (ulPacketNum * 1000 / pDevice->uDiversityCnt);
        //ulRatio = (pDevice->uNumSQ3[RATE_12M] * 1000 / pDevice->uDiversityCnt);
        ulRatio += TOP_RATE_12M;
        ulMaxPacket = pDevice->uNumSQ3[RATE_12M];
    }
    if ( pDevice->uNumSQ3[RATE_11M] > ulMaxPacket ) {
        ulPacketNum = pDevice->uDiversityCnt - pDevice->uNumSQ3[RATE_1M] -
                      pDevice->uNumSQ3[RATE_2M] - pDevice->uNumSQ3[RATE_5M] -
                      pDevice->uNumSQ3[RATE_6M] - pDevice->uNumSQ3[RATE_9M];
        ulRatio = (ulPacketNum * 1000 / pDevice->uDiversityCnt);
        //ulRatio = (pDevice->uNumSQ3[RATE_11M] * 1000 / pDevice->uDiversityCnt);
        ulRatio += TOP_RATE_11M;
        ulMaxPacket = pDevice->uNumSQ3[RATE_11M];
    }
    if ( pDevice->uNumSQ3[RATE_9M] > ulMaxPacket ) {
        ulPacketNum = pDevice->uDiversityCnt - pDevice->uNumSQ3[RATE_1M] -
                      pDevice->uNumSQ3[RATE_2M] - pDevice->uNumSQ3[RATE_5M] -
                      pDevice->uNumSQ3[RATE_6M];
        ulRatio = (ulPacketNum * 1000 / pDevice->uDiversityCnt);
        //ulRatio = (pDevice->uNumSQ3[RATE_9M] * 1000 / pDevice->uDiversityCnt);
        ulRatio += TOP_RATE_9M;
        ulMaxPacket = pDevice->uNumSQ3[RATE_9M];
    }
    if ( pDevice->uNumSQ3[RATE_6M] > ulMaxPacket ) {
        ulPacketNum = pDevice->uDiversityCnt - pDevice->uNumSQ3[RATE_1M] -
                      pDevice->uNumSQ3[RATE_2M] - pDevice->uNumSQ3[RATE_5M];
        ulRatio = (ulPacketNum * 1000 / pDevice->uDiversityCnt);
        //ulRatio = (pDevice->uNumSQ3[RATE_6M] * 1000 / pDevice->uDiversityCnt);
        ulRatio += TOP_RATE_6M;
        ulMaxPacket = pDevice->uNumSQ3[RATE_6M];
    }
    if ( pDevice->uNumSQ3[RATE_5M] > ulMaxPacket ) {
        ulPacketNum = pDevice->uDiversityCnt - pDevice->uNumSQ3[RATE_1M] -
                      pDevice->uNumSQ3[RATE_2M];
        ulRatio = (ulPacketNum * 1000 / pDevice->uDiversityCnt);
        //ulRatio = (pDevice->uNumSQ3[RATE_5M] * 1000 / pDevice->uDiversityCnt);
        ulRatio += TOP_RATE_55M;
        ulMaxPacket = pDevice->uNumSQ3[RATE_5M];
    }
    if ( pDevice->uNumSQ3[RATE_2M] > ulMaxPacket ) {
        ulPacketNum = pDevice->uDiversityCnt - pDevice->uNumSQ3[RATE_1M];
        ulRatio = (ulPacketNum * 1000 / pDevice->uDiversityCnt);
        //ulRatio = (pDevice->uNumSQ3[RATE_2M]  * 1000 / pDevice->uDiversityCnt);
        ulRatio += TOP_RATE_2M;
        ulMaxPacket = pDevice->uNumSQ3[RATE_2M];
    }
    if ( pDevice->uNumSQ3[RATE_1M] > ulMaxPacket ) {
        ulPacketNum = pDevice->uDiversityCnt;
        ulRatio = (ulPacketNum * 1000 / pDevice->uDiversityCnt);
        //ulRatio = (pDevice->uNumSQ3[RATE_1M]  * 1000 / pDevice->uDiversityCnt);
        ulRatio += TOP_RATE_1M;
    }

    return ulRatio;
}