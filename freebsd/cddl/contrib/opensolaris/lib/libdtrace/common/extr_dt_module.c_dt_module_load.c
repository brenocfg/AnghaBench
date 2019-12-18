#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_9__ ;
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dt_sym_t ;
struct TYPE_11__ {char* cts_name; int cts_size; int cts_entsize; scalar_t__ cts_offset; int /*<<< orphan*/ * cts_data; scalar_t__ cts_flags; int /*<<< orphan*/  cts_type; } ;
struct TYPE_10__ {int dm_flags; scalar_t__ dm_pid; int dm_nsymelems; int dm_nsymbuckets; int dm_symfree; int dm_asrsv; int dm_aslen; TYPE_6__ dm_symtab; int /*<<< orphan*/  dm_name; TYPE_9__* dm_ops; int /*<<< orphan*/ * dm_asmap; int /*<<< orphan*/ * dm_symchains; int /*<<< orphan*/ * dm_symbuckets; TYPE_6__ dm_strtab; TYPE_6__ dm_ctdata; } ;
typedef  TYPE_1__ dt_module_t ;
struct TYPE_12__ {int (* do_syminit ) (TYPE_1__*) ;int /*<<< orphan*/  (* do_symsort ) (TYPE_1__*) ;} ;
typedef  int /*<<< orphan*/  Elf64_Sym ;
typedef  int /*<<< orphan*/  Elf32_Sym ;

/* Variables and functions */
 int DT_DM_LOADED ; 
 int /*<<< orphan*/  EDT_NOMEM ; 
 int /*<<< orphan*/  SHT_PROGBITS ; 
 int /*<<< orphan*/  SHT_STRTAB ; 
 int /*<<< orphan*/  SHT_SYMTAB ; 
 int _dtrace_strbuckets ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  dt_dprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_9__ dt_modops_64 ; 
 int dt_module_load_proc (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int dt_module_load_sect (int /*<<< orphan*/ *,TYPE_1__*,TYPE_6__*) ; 
 int /*<<< orphan*/  dt_module_unload (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int dt_set_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 

int
dt_module_load(dtrace_hdl_t *dtp, dt_module_t *dmp)
{
	if (dmp->dm_flags & DT_DM_LOADED)
		return (0); /* module is already loaded */

	if (dmp->dm_pid != 0)
		return (dt_module_load_proc(dtp, dmp));

	dmp->dm_ctdata.cts_name = ".SUNW_ctf";
	dmp->dm_ctdata.cts_type = SHT_PROGBITS;
	dmp->dm_ctdata.cts_flags = 0;
	dmp->dm_ctdata.cts_data = NULL;
	dmp->dm_ctdata.cts_size = 0;
	dmp->dm_ctdata.cts_entsize = 0;
	dmp->dm_ctdata.cts_offset = 0;

	dmp->dm_symtab.cts_name = ".symtab";
	dmp->dm_symtab.cts_type = SHT_SYMTAB;
	dmp->dm_symtab.cts_flags = 0;
	dmp->dm_symtab.cts_data = NULL;
	dmp->dm_symtab.cts_size = 0;
	dmp->dm_symtab.cts_entsize = dmp->dm_ops == &dt_modops_64 ?
	    sizeof (Elf64_Sym) : sizeof (Elf32_Sym);
	dmp->dm_symtab.cts_offset = 0;

	dmp->dm_strtab.cts_name = ".strtab";
	dmp->dm_strtab.cts_type = SHT_STRTAB;
	dmp->dm_strtab.cts_flags = 0;
	dmp->dm_strtab.cts_data = NULL;
	dmp->dm_strtab.cts_size = 0;
	dmp->dm_strtab.cts_entsize = 0;
	dmp->dm_strtab.cts_offset = 0;

	/*
	 * Attempt to load the module's CTF section, symbol table section, and
	 * string table section.  Note that modules may not contain CTF data:
	 * this will result in a successful load_sect but data of size zero.
	 * We will then fail if dt_module_getctf() is called, as shown below.
	 */
	if (dt_module_load_sect(dtp, dmp, &dmp->dm_ctdata) == -1 ||
	    dt_module_load_sect(dtp, dmp, &dmp->dm_symtab) == -1 ||
	    dt_module_load_sect(dtp, dmp, &dmp->dm_strtab) == -1) {
		dt_module_unload(dtp, dmp);
		return (-1); /* dt_errno is set for us */
	}

	/*
	 * Allocate the hash chains and hash buckets for symbol name lookup.
	 * This is relatively simple since the symbol table is of fixed size
	 * and is known in advance.  We allocate one extra element since we
	 * use element indices instead of pointers and zero is our sentinel.
	 */
	dmp->dm_nsymelems =
	    dmp->dm_symtab.cts_size / dmp->dm_symtab.cts_entsize;

	dmp->dm_nsymbuckets = _dtrace_strbuckets;
	dmp->dm_symfree = 1;		/* first free element is index 1 */

	dmp->dm_symbuckets = calloc(dmp->dm_nsymbuckets, sizeof (uint_t));
	dmp->dm_symchains = calloc(dmp->dm_nsymelems + 1, sizeof (dt_sym_t));

	if (dmp->dm_symbuckets == NULL || dmp->dm_symchains == NULL) {
		dt_module_unload(dtp, dmp);
		return (dt_set_errno(dtp, EDT_NOMEM));
	}

	/*
	 * Iterate over the symbol table data buffer and insert each symbol
	 * name into the name hash if the name and type are valid.  Then
	 * allocate the address map, fill it in, and sort it.
	 */
	dmp->dm_asrsv = dmp->dm_ops->do_syminit(dmp);

	dt_dprintf("hashed %s [%s] (%u symbols)\n",
	    dmp->dm_name, dmp->dm_symtab.cts_name, dmp->dm_symfree - 1);

	if ((dmp->dm_asmap = malloc(sizeof (void *) * dmp->dm_asrsv)) == NULL) {
		dt_module_unload(dtp, dmp);
		return (dt_set_errno(dtp, EDT_NOMEM));
	}

	dmp->dm_ops->do_symsort(dmp);

	dt_dprintf("sorted %s [%s] (%u symbols)\n",
	    dmp->dm_name, dmp->dm_symtab.cts_name, dmp->dm_aslen);

	dmp->dm_flags |= DT_DM_LOADED;
	return (0);
}