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
typedef  size_t u8 ;

/* Variables and functions */
 int /*<<< orphan*/  MPTUNKNOWN_DRIVER ; 
 size_t MPT_MAX_PROTOCOL_DRIVERS ; 
 int /*<<< orphan*/ ** MptCallbacks ; 
 int /*<<< orphan*/ * MptDriverClass ; 
 int /*<<< orphan*/ ** MptEvHandlers ; 
 int /*<<< orphan*/  last_drv_idx ; 

void
mpt_deregister(u8 cb_idx)
{
	if (cb_idx && (cb_idx < MPT_MAX_PROTOCOL_DRIVERS)) {
		MptCallbacks[cb_idx] = NULL;
		MptDriverClass[cb_idx] = MPTUNKNOWN_DRIVER;
		MptEvHandlers[cb_idx] = NULL;

		last_drv_idx++;
	}
}