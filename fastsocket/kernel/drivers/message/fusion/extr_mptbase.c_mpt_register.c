#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  MPT_DRIVER_CLASS ;
typedef  int /*<<< orphan*/ * MPT_CALLBACK ;

/* Variables and functions */
 scalar_t__ MPT_MAX_CALLBACKNAME_LEN ; 
 int MPT_MAX_PROTOCOL_DRIVERS ; 
 int /*<<< orphan*/ ** MptCallbacks ; 
 int /*<<< orphan*/ * MptCallbacksName ; 
 int /*<<< orphan*/ * MptDriverClass ; 
 int /*<<< orphan*/ ** MptEvHandlers ; 
 int last_drv_idx ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,scalar_t__) ; 

u8
mpt_register(MPT_CALLBACK cbfunc, MPT_DRIVER_CLASS dclass, char *func_name)
{
	u8 cb_idx;
	last_drv_idx = MPT_MAX_PROTOCOL_DRIVERS;

	/*
	 *  Search for empty callback slot in this order: {N,...,7,6,5,...,1}
	 *  (slot/handle 0 is reserved!)
	 */
	for (cb_idx = MPT_MAX_PROTOCOL_DRIVERS-1; cb_idx; cb_idx--) {
		if (MptCallbacks[cb_idx] == NULL) {
			MptCallbacks[cb_idx] = cbfunc;
			MptDriverClass[cb_idx] = dclass;
			MptEvHandlers[cb_idx] = NULL;
			last_drv_idx = cb_idx;
			strlcpy(MptCallbacksName[cb_idx], func_name,
				MPT_MAX_CALLBACKNAME_LEN+1);
			break;
		}
	}

	return last_drv_idx;
}