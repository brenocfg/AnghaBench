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
typedef  TYPE_1__* pMWAVE_DEVICE_DATA ;
struct TYPE_3__ {size_t nr_registered_attrs; scalar_t__ sLine; int /*<<< orphan*/  rBDData; scalar_t__ bBDInitialized; scalar_t__ bResourcesClaimed; scalar_t__ bDSPEnabled; scalar_t__ bMwaveDevRegistered; scalar_t__ device_registered; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  PRINTK_1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRACE_MWAVE ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 size_t i ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mwave_dev_attrs ; 
 int /*<<< orphan*/  mwave_device ; 
 int /*<<< orphan*/  mwave_misc_dev ; 
 TYPE_1__ mwave_s_mdd ; 
 int /*<<< orphan*/  serial8250_unregister_port (scalar_t__) ; 
 int /*<<< orphan*/  tp3780I_Cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tp3780I_DisableDSP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tp3780I_ReleaseResources (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mwave_exit(void)
{
	pMWAVE_DEVICE_DATA pDrvData = &mwave_s_mdd;

	PRINTK_1(TRACE_MWAVE, "mwavedd::mwave_exit entry\n");

#if 0
	for (i = 0; i < pDrvData->nr_registered_attrs; i++)
		device_remove_file(&mwave_device, mwave_dev_attrs[i]);
	pDrvData->nr_registered_attrs = 0;

	if (pDrvData->device_registered) {
		device_unregister(&mwave_device);
		pDrvData->device_registered = FALSE;
	}
#endif

	if ( pDrvData->sLine >= 0 ) {
		serial8250_unregister_port(pDrvData->sLine);
	}
	if (pDrvData->bMwaveDevRegistered) {
		misc_deregister(&mwave_misc_dev);
	}
	if (pDrvData->bDSPEnabled) {
		tp3780I_DisableDSP(&pDrvData->rBDData);
	}
	if (pDrvData->bResourcesClaimed) {
		tp3780I_ReleaseResources(&pDrvData->rBDData);
	}
	if (pDrvData->bBDInitialized) {
		tp3780I_Cleanup(&pDrvData->rBDData);
	}

	PRINTK_1(TRACE_MWAVE, "mwavedd::mwave_exit exit\n");
}