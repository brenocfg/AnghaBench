#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ipc_voucher_t ;
struct TYPE_4__ {int /*<<< orphan*/  iv_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  iv_dealloc (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ os_ref_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
iv_release(ipc_voucher_t iv)
{
	if (os_ref_release(&iv->iv_refs) == 0) {
		iv_dealloc(iv, TRUE);
	}
}