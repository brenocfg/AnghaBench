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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  nstat_sysinfo_string; } ;
struct TYPE_5__ {int nstat_sysinfo_key; int /*<<< orphan*/  nstat_sysinfo_valsize; TYPE_1__ u; int /*<<< orphan*/  nstat_sysinfo_flags; } ;
typedef  TYPE_2__ nstat_sysinfo_keyval ;

/* Variables and functions */
 int /*<<< orphan*/  NSTAT_SYSINFO_FLAG_STRING ; 
 int /*<<< orphan*/  NSTAT_SYSINFO_KEYVAL_STRING_MAXSIZE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nstat_set_keyval_string(nstat_sysinfo_keyval *kv, int key, u_int8_t *buf,
    u_int32_t len)
{
	kv->nstat_sysinfo_key = key;
	kv->nstat_sysinfo_flags = NSTAT_SYSINFO_FLAG_STRING;
	kv->nstat_sysinfo_valsize = min(len,
	    NSTAT_SYSINFO_KEYVAL_STRING_MAXSIZE);
	bcopy(buf, kv->u.nstat_sysinfo_string, kv->nstat_sysinfo_valsize);
}