#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int ushort_t ;
typedef  int /*<<< orphan*/  tdesc_t ;
struct TYPE_10__ {int /*<<< orphan*/  td_iihash; } ;
typedef  TYPE_1__ tdata_t ;
typedef  int /*<<< orphan*/  symit_data_t ;
struct TYPE_11__ {scalar_t__ ii_type; char* ii_owner; int /*<<< orphan*/  ii_name; int /*<<< orphan*/ * ii_dtype; } ;
typedef  TYPE_2__ iidesc_t ;
struct TYPE_12__ {scalar_t__ cth_objtoff; size_t cth_funcoff; } ;
typedef  TYPE_3__ ctf_header_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_13__ {int /*<<< orphan*/  st_info; } ;
typedef  TYPE_4__ GElf_Sym ;

/* Variables and functions */
 scalar_t__ GELF_ST_BIND (int /*<<< orphan*/ ) ; 
 scalar_t__ II_GVAR ; 
 scalar_t__ II_SVAR ; 
 scalar_t__ STB_LOCAL ; 
 int /*<<< orphan*/  STT_OBJECT ; 
 int /*<<< orphan*/  debug (int,char*,...) ; 
 int /*<<< orphan*/  hash_add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* iidesc_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parseterminate (char*,int,...) ; 
 int /*<<< orphan*/  symit_curfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symit_name (int /*<<< orphan*/ *) ; 
 TYPE_4__* symit_next (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symit_reset (int /*<<< orphan*/ *) ; 
 char* xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
resurrect_objects(ctf_header_t *h, tdata_t *td, tdesc_t **tdarr, int tdsize,
    caddr_t ctfdata, symit_data_t *si)
{
	caddr_t buf = ctfdata + h->cth_objtoff;
	size_t bufsz = h->cth_funcoff - h->cth_objtoff;
	caddr_t dptr;

	symit_reset(si);
	for (dptr = buf; dptr < buf + bufsz; dptr += 2) {
		void *v = (void *) dptr;
		ushort_t id = *((ushort_t *)v);
		iidesc_t *ii;
		GElf_Sym *sym;

		if (!(sym = symit_next(si, STT_OBJECT)) && id != 0) {
			parseterminate(
			    "Unexpected end of object symbols at %x of %x",
			    dptr - buf, bufsz);
		}

		if (id == 0) {
			debug(3, "Skipping null object\n");
			continue;
		} else if (id >= tdsize) {
			parseterminate("Reference to invalid type %d", id);
		}

		ii = iidesc_new(symit_name(si));
		ii->ii_dtype = tdarr[id];
		if (GELF_ST_BIND(sym->st_info) == STB_LOCAL) {
			ii->ii_type = II_SVAR;
			ii->ii_owner = xstrdup(symit_curfile(si));
		} else
			ii->ii_type = II_GVAR;
		hash_add(td->td_iihash, ii);

		debug(3, "Resurrected %s object %s (%d) from %s\n",
		    (ii->ii_type == II_GVAR ? "global" : "static"),
		    ii->ii_name, id, (ii->ii_owner ? ii->ii_owner : "(none)"));
	}
}