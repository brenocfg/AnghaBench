#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  nstat_sysinfo_scalar; } ;
struct TYPE_5__ {int nstat_sysinfo_key; int nstat_sysinfo_valsize; TYPE_1__ u; int /*<<< orphan*/  nstat_sysinfo_flags; } ;
typedef  TYPE_2__ nstat_sysinfo_keyval ;

/* Variables and functions */
 int /*<<< orphan*/  NSTAT_SYSINFO_FLAG_SCALAR ; 

__attribute__((used)) static void
nstat_set_keyval_scalar(nstat_sysinfo_keyval *kv, int key, u_int32_t val)
{
	kv->nstat_sysinfo_key = key;
	kv->nstat_sysinfo_flags = NSTAT_SYSINFO_FLAG_SCALAR;
	kv->u.nstat_sysinfo_scalar = val;
	kv->nstat_sysinfo_valsize = sizeof(kv->u.nstat_sysinfo_scalar);
}