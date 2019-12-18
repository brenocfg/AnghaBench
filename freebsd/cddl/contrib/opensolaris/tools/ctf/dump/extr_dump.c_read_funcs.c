#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ushort_t ;
typedef  scalar_t__ ulong_t ;
struct TYPE_7__ {int cth_funcoff; int cth_typeoff; } ;
typedef  TYPE_1__ ctf_header_t ;
struct TYPE_8__ {int cd_ctflen; int /*<<< orphan*/ * cd_symdata; scalar_t__ cd_ctfdata; } ;
typedef  TYPE_2__ ctf_data_t ;
struct TYPE_9__ {scalar_t__ s_nargs; int /*<<< orphan*/  s_argmax; int /*<<< orphan*/  s_nfunc; } ;

/* Variables and functions */
 scalar_t__ CTF_INFO_KIND (scalar_t__) ; 
 scalar_t__ CTF_INFO_VLEN (scalar_t__) ; 
 scalar_t__ CTF_K_FUNCTION ; 
 scalar_t__ CTF_K_UNKNOWN ; 
 int E_ERROR ; 
 int E_SUCCESS ; 
 scalar_t__ F_STATS ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  STT_FUNC ; 
 int /*<<< orphan*/  WARN (char*) ; 
 scalar_t__ flags ; 
 int next_sym (TYPE_2__ const*,int,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  print_line (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_3__ stats ; 

__attribute__((used)) static int
read_funcs(const ctf_header_t *hp, const ctf_data_t *cd)
{
	void *v = (void *) (cd->cd_ctfdata + hp->cth_funcoff);
	const ushort_t *fp = v;

	v = (void *) (cd->cd_ctfdata + hp->cth_typeoff);
	const ushort_t *end = v;

	ulong_t id;
	int symidx;

	if (flags != F_STATS)
		print_line("- Functions ");

	if (hp->cth_funcoff & 1)
		WARN("cth_funcoff is not aligned properly\n");
	if (hp->cth_funcoff >= cd->cd_ctflen)
		WARN("file is truncated or cth_funcoff is corrupt\n");
	if (hp->cth_typeoff >= cd->cd_ctflen)
		WARN("file is truncated or cth_typeoff is corrupt\n");
	if (hp->cth_funcoff > hp->cth_typeoff)
		WARN("file is corrupt -- cth_funcoff > cth_typeoff\n");

	for (symidx = -1, id = 0; fp < end; id++) {
		ushort_t info = *fp++;
		ushort_t kind = CTF_INFO_KIND(info);
		ushort_t n = CTF_INFO_VLEN(info);
		ushort_t i;
		int nextsym;
		char *name;

		if (cd->cd_symdata == NULL || (nextsym = next_sym(cd, symidx,
		    STT_FUNC, &name)) < 0)
			name = NULL;
		else
			symidx = nextsym;

		if (kind == CTF_K_UNKNOWN && n == 0)
			continue; /* skip padding */

		if (kind != CTF_K_FUNCTION) {
			(void) printf("  [%lu] unexpected kind -- %u\n",
			    id, kind);
			return (E_ERROR);
		}

		if (fp + n > end) {
			(void) printf("  [%lu] vlen %u extends past section "
			    "boundary\n", id, n);
			return (E_ERROR);
		}

		if (flags != F_STATS) {
			(void) printf("  [%lu] FUNC ", id);
			if (name != NULL)
				(void) printf("(%s) ", name);
			(void) printf("returns: %u args: (", *fp++);

			if (n != 0) {
				(void) printf("%u", *fp++);
				for (i = 1; i < n; i++)
					(void) printf(", %u", *fp++);
			}

			(void) printf(")\n");
		} else
			fp += n + 1; /* skip to next function definition */

		stats.s_nfunc++;
		stats.s_nargs += n;
		stats.s_argmax = MAX(stats.s_argmax, n);
	}

	return (E_SUCCESS);
}