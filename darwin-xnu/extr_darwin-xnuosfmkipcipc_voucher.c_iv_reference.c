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
typedef  TYPE_1__* ipc_voucher_t ;
struct TYPE_3__ {int /*<<< orphan*/  iv_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_ref_retain (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
iv_reference(ipc_voucher_t iv)
{
	os_ref_retain(&iv->iv_refs);
}