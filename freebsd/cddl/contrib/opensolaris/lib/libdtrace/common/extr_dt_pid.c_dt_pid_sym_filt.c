#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ st_shndx; scalar_t__ st_size; scalar_t__ st_value; } ;
struct TYPE_6__ {scalar_t__ dpp_last_taken; TYPE_2__ dpp_last; int /*<<< orphan*/  dpp_func; } ;
typedef  TYPE_1__ dt_pid_probe_t ;
typedef  TYPE_2__ GElf_Sym ;

/* Variables and functions */
 scalar_t__ SHN_UNDEF ; 
 int /*<<< orphan*/  dt_dprintf (char*,char const*) ; 
 int dt_pid_per_sym (TYPE_1__*,TYPE_2__ const*,char const*) ; 
 scalar_t__ gmatch (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
dt_pid_sym_filt(void *arg, const GElf_Sym *symp, const char *func)
{
	dt_pid_probe_t *pp = arg;

	if (symp->st_shndx == SHN_UNDEF)
		return (0);

	if (symp->st_size == 0) {
		dt_dprintf("st_size of %s is zero\n", func);
		return (0);
	}

	if (pp->dpp_last_taken == 0 ||
	    symp->st_value != pp->dpp_last.st_value ||
	    symp->st_size != pp->dpp_last.st_size) {
		/*
		 * Due to 4524008, _init and _fini may have a bloated st_size.
		 * While this bug has been fixed for a while, old binaries
		 * may exist that still exhibit this problem. As a result, we
		 * don't match _init and _fini though we allow users to
		 * specify them explicitly.
		 */
		if (strcmp(func, "_init") == 0 || strcmp(func, "_fini") == 0)
			return (0);

		if ((pp->dpp_last_taken = gmatch(func, pp->dpp_func)) != 0) {
			pp->dpp_last = *symp;
			return (dt_pid_per_sym(pp, symp, func));
		}
	}

	return (0);
}