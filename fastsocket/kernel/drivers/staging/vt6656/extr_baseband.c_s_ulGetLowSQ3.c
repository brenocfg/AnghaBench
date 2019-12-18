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
struct TYPE_3__ {int* aulPktNum; int* aulSQ3Val; } ;
typedef  TYPE_1__* PSDevice ;

/* Variables and functions */
 int RATE_48M ; 
 size_t RATE_54M ; 
 int RATE_6M ; 

__attribute__((used)) static
ULONG
s_ulGetLowSQ3(PSDevice pDevice)
{
int   ii;
ULONG ulSQ3 = 0;
ULONG ulMaxPacket;

    ulMaxPacket = pDevice->aulPktNum[RATE_54M];
    if ( pDevice->aulPktNum[RATE_54M] != 0 ) {
        ulSQ3 = pDevice->aulSQ3Val[RATE_54M] / pDevice->aulPktNum[RATE_54M];
    }
    for ( ii=RATE_48M;ii>=RATE_6M;ii-- ) {
        if ( pDevice->aulPktNum[ii] > ulMaxPacket ) {
            ulMaxPacket = pDevice->aulPktNum[ii];
            ulSQ3 = pDevice->aulSQ3Val[ii] / pDevice->aulPktNum[ii];
        }
    }

    return ulSQ3;
}