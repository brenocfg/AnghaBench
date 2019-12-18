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
struct cred {int /*<<< orphan*/  cap_effective; } ;
typedef  int /*<<< orphan*/  kernel_cap_t ;

/* Variables and functions */
 scalar_t__ current_cred () ; 

__attribute__((used)) static void fsocket_reset_bind_cap(kernel_cap_t *p)
{
	struct cred *old;

	old = (struct cred *)current_cred();
	old->cap_effective = *p;
}