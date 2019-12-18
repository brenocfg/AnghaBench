#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_9__ {int /*<<< orphan*/  dm_name; int /*<<< orphan*/  dm_elf; } ;
typedef  TYPE_1__ dt_module_t ;
struct TYPE_10__ {scalar_t__ cts_type; scalar_t__ cts_entsize; scalar_t__ cts_size; int /*<<< orphan*/  cts_name; int /*<<< orphan*/ * cts_data; } ;
typedef  TYPE_2__ ctf_sect_t ;
struct TYPE_12__ {scalar_t__ d_size; int /*<<< orphan*/ * d_buf; } ;
struct TYPE_11__ {scalar_t__ sh_type; scalar_t__ sh_entsize; int /*<<< orphan*/  sh_name; } ;
typedef  TYPE_3__ GElf_Shdr ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  TYPE_4__ Elf_Data ;

/* Variables and functions */
 int /*<<< orphan*/  EDT_NOTLOADED ; 
 scalar_t__ SHT_NULL ; 
 int /*<<< orphan*/  dt_dprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dt_set_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* elf_getdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int elf_getshdrstrndx (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/ * elf_nextscn (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* elf_strptr (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gelf_getshdr (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dt_module_load_sect(dtrace_hdl_t *dtp, dt_module_t *dmp, ctf_sect_t *ctsp)
{
	const char *s;
	size_t shstrs;
	GElf_Shdr sh;
	Elf_Data *dp;
	Elf_Scn *sp;

	if (elf_getshdrstrndx(dmp->dm_elf, &shstrs) == -1)
		return (dt_set_errno(dtp, EDT_NOTLOADED));

	for (sp = NULL; (sp = elf_nextscn(dmp->dm_elf, sp)) != NULL; ) {
		if (gelf_getshdr(sp, &sh) == NULL || sh.sh_type == SHT_NULL ||
		    (s = elf_strptr(dmp->dm_elf, shstrs, sh.sh_name)) == NULL)
			continue; /* skip any malformed sections */

		if (sh.sh_type == ctsp->cts_type &&
		    sh.sh_entsize == ctsp->cts_entsize &&
		    strcmp(s, ctsp->cts_name) == 0)
			break; /* section matches specification */
	}

	/*
	 * If the section isn't found, return success but leave cts_data set
	 * to NULL and cts_size set to zero for our caller.
	 */
	if (sp == NULL || (dp = elf_getdata(sp, NULL)) == NULL)
		return (0);

#ifdef illumos
	ctsp->cts_data = dp->d_buf;
#else
	if ((ctsp->cts_data = malloc(dp->d_size)) == NULL)
		return (0);
	memcpy(ctsp->cts_data, dp->d_buf, dp->d_size);
#endif
	ctsp->cts_size = dp->d_size;

	dt_dprintf("loaded %s [%s] (%lu bytes)\n",
	    dmp->dm_name, ctsp->cts_name, (ulong_t)ctsp->cts_size);

	return (0);
}