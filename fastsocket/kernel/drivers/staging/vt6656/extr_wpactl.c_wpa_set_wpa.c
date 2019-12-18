#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct viawget_wpa_param {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  bShareKeyAlgorithm; int /*<<< orphan*/  eAuthenMode; } ;
struct TYPE_5__ {TYPE_1__ sMgmtObj; } ;
typedef  TYPE_1__* PSMgmtObject ;
typedef  TYPE_2__* PSDevice ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  WMAC_AUTH_OPEN ; 

__attribute__((used)) static int wpa_set_wpa(PSDevice pDevice,
				     struct viawget_wpa_param *param)
{

    PSMgmtObject    pMgmt = &(pDevice->sMgmtObj);
	int ret = 0;

    pMgmt->eAuthenMode = WMAC_AUTH_OPEN;
    pMgmt->bShareKeyAlgorithm = FALSE;

    return ret;
}