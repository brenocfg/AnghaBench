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
struct TYPE_2__ {int wBasicRate; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PSDevice ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int RATE_54M ; 
 int RATE_6M ; 
 int /*<<< orphan*/  TRUE ; 

BOOL CARDbIsOFDMinBasicRate (PVOID pDeviceHandler)
{
PSDevice    pDevice = (PSDevice) pDeviceHandler;
int ii;

    for (ii = RATE_54M; ii >= RATE_6M; ii --) {
        if ((pDevice->wBasicRate) & ((WORD)(1<<ii)))
            return TRUE;
    }
    return FALSE;
}