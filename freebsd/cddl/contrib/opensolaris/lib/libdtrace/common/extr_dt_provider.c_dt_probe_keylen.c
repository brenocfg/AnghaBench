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
struct TYPE_3__ {int /*<<< orphan*/  dtpd_name; int /*<<< orphan*/  dtpd_func; int /*<<< orphan*/  dtpd_mod; } ;
typedef  TYPE_1__ dtrace_probedesc_t ;

/* Variables and functions */
 size_t strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
dt_probe_keylen(const dtrace_probedesc_t *pdp)
{
	return (strlen(pdp->dtpd_mod) + 1 +
	    strlen(pdp->dtpd_func) + 1 + strlen(pdp->dtpd_name) + 1);
}