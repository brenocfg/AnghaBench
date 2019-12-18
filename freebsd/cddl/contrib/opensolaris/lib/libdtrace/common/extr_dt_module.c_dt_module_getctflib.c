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
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_3__ {int dm_nctflibs; int /*<<< orphan*/ ** dm_libctfp; int /*<<< orphan*/ * dm_libctfn; } ;
typedef  TYPE_1__ dt_module_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

ctf_file_t *
dt_module_getctflib(dtrace_hdl_t *dtp, dt_module_t *dmp, const char *name)
{
	int i;

	for (i = 0; i < dmp->dm_nctflibs; i++) {
		if (strcmp(dmp->dm_libctfn[i], name) == 0)
			return (dmp->dm_libctfp[i]);
	}

	return (NULL);
}