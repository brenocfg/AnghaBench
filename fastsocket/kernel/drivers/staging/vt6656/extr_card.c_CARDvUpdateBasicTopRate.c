#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
struct TYPE_2__ {int wBasicRate; int byTopOFDMBasicRate; int byTopCCKBasicRate; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PSDevice ;
typedef  int BYTE ;

/* Variables and functions */
 int RATE_11M ; 
 int RATE_1M ; 
 int RATE_24M ; 
 int RATE_54M ; 
 int RATE_6M ; 

void CARDvUpdateBasicTopRate (PVOID pDeviceHandler)
{
PSDevice    pDevice = (PSDevice) pDeviceHandler;
BYTE byTopOFDM = RATE_24M, byTopCCK = RATE_1M;
BYTE ii;

     //Determines the highest basic rate.
     for (ii = RATE_54M; ii >= RATE_6M; ii --) {
         if ( (pDevice->wBasicRate) & ((WORD)(1<<ii)) ) {
             byTopOFDM = ii;
             break;
         }
     }
     pDevice->byTopOFDMBasicRate = byTopOFDM;

     for (ii = RATE_11M;; ii --) {
         if ( (pDevice->wBasicRate) & ((WORD)(1<<ii)) ) {
             byTopCCK = ii;
             break;
         }
         if (ii == RATE_1M)
            break;
     }
     pDevice->byTopCCKBasicRate = byTopCCK;
 }