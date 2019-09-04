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
struct TYPE_3__ {int /*<<< orphan*/  dtpk_name; int /*<<< orphan*/  dtpk_func; int /*<<< orphan*/  dtpk_mod; int /*<<< orphan*/  dtpk_prov; } ;
typedef  TYPE_1__ dtrace_probekey_t ;

/* Variables and functions */
 int /*<<< orphan*/  dtrace_strunref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dtrace_probekey_release(dtrace_probekey_t *pkp)
{
	dtrace_strunref(pkp->dtpk_prov);
	dtrace_strunref(pkp->dtpk_mod);
	dtrace_strunref(pkp->dtpk_func);
	dtrace_strunref(pkp->dtpk_name);
}