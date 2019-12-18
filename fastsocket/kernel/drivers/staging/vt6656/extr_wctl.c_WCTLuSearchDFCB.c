#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_8__ {int /*<<< orphan*/ * abyAddr2; } ;
struct TYPE_7__ {size_t cbDFCB; TYPE_1__* sRxDFCB; } ;
struct TYPE_6__ {scalar_t__ bInUse; int /*<<< orphan*/ * abyAddr2; } ;
typedef  TYPE_2__* PSDevice ;
typedef  TYPE_3__* PS802_11Header ;

/* Variables and functions */
 scalar_t__ IS_ETH_ADDRESS_EQUAL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 

UINT WCTLuSearchDFCB (PSDevice pDevice, PS802_11Header pMACHeader)
{
UINT ii;

    for(ii=0;ii<pDevice->cbDFCB;ii++) {
        if ((pDevice->sRxDFCB[ii].bInUse == TRUE) &&
            (IS_ETH_ADDRESS_EQUAL (&(pDevice->sRxDFCB[ii].abyAddr2[0]), &(pMACHeader->abyAddr2[0])))
            ) {
            //
            return(ii);
        }
    }
    return(pDevice->cbDFCB);
}