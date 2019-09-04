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
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  hv_callbacks_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  hv_callbacks ; 
 int hv_callbacks_enabled ; 
 int /*<<< orphan*/  hv_support_lck_mtx ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 

kern_return_t
hv_set_callbacks(hv_callbacks_t callbacks) {
	kern_return_t kr = KERN_FAILURE;

	lck_mtx_lock(hv_support_lck_mtx);
	if (hv_callbacks_enabled == 0) {	
		hv_callbacks = callbacks;
		hv_callbacks_enabled = 1;
		kr = KERN_SUCCESS;
	}
	lck_mtx_unlock(hv_support_lck_mtx);

	return kr;
}