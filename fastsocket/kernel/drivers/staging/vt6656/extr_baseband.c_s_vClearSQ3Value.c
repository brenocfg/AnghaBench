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
struct TYPE_3__ {scalar_t__* aulSQ3Val; scalar_t__* aulPktNum; scalar_t__ uDiversityCnt; } ;
typedef  TYPE_1__* PSDevice ;

/* Variables and functions */
 int MAX_RATE ; 
 int RATE_1M ; 

__attribute__((used)) static
void
s_vClearSQ3Value (PSDevice pDevice)
{
    int ii;
    pDevice->uDiversityCnt = 0;

    for ( ii=RATE_1M;ii<MAX_RATE;ii++) {
        pDevice->aulPktNum[ii] = 0;
        pDevice->aulSQ3Val[ii] = 0;
    }
}