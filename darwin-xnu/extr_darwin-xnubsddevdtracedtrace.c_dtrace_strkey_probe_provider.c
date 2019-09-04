#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* dtpr_provider; } ;
typedef  TYPE_2__ dtrace_probe_t ;
struct TYPE_3__ {char const* dtpv_name; } ;

/* Variables and functions */

__attribute__((used)) static const char*
dtrace_strkey_probe_provider(void *elm, uintptr_t offs)
{
#pragma unused(offs)
	dtrace_probe_t *probe = (dtrace_probe_t*)elm;
	return probe->dtpr_provider->dtpv_name;
}