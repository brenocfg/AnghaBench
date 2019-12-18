#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct elfcopy {scalar_t__* secndx; scalar_t__ strip; int flags; int /*<<< orphan*/ * v_rel; int /*<<< orphan*/ * v_grp; } ;
struct TYPE_6__ {size_t member_5; size_t st_shndx; int /*<<< orphan*/  st_info; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ GElf_Sym ;

/* Variables and functions */
 scalar_t__ BIT_ISSET (int /*<<< orphan*/ *,int) ; 
 int DISCARD_LLABEL ; 
 int DISCARD_LOCAL ; 
 size_t SHN_LORESERVE ; 
 size_t SHN_UNDEF ; 
 scalar_t__ STRIP_ALL ; 
 scalar_t__ STRIP_DEBUG ; 
 scalar_t__ STRIP_UNNEEDED ; 
 int /*<<< orphan*/  SYMOP_KEEP ; 
 int /*<<< orphan*/  SYMOP_STRIP ; 
 scalar_t__ is_debug_symbol (int /*<<< orphan*/ ) ; 
 scalar_t__ is_local_label (char const*) ; 
 scalar_t__ is_local_symbol (int /*<<< orphan*/ ) ; 
 scalar_t__ is_needed_symbol (struct elfcopy*,int,TYPE_1__*) ; 
 int /*<<< orphan*/ * lookup_symop_list (struct elfcopy*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_reloc_symbols (struct elfcopy*,size_t) ; 
 int /*<<< orphan*/  mark_section_group_symbols (struct elfcopy*,size_t) ; 
 int /*<<< orphan*/  memcmp (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static int
is_remove_symbol(struct elfcopy *ecp, size_t sc, int i, GElf_Sym *s,
    const char *name)
{
	GElf_Sym sym0 = {
		0, 		/* st_name */
		0,		/* st_value */
		0,		/* st_size */
		0,		/* st_info */
		0,		/* st_other */
		SHN_UNDEF,	/* st_shndx */
	};

	/*
	 * Keep the first symbol if it is the special reserved symbol.
	 * XXX Should we generate one if it's missing?
	 */
	if (i == 0 && !memcmp(s, &sym0, sizeof(GElf_Sym)))
		return (0);

	/* Remove the symbol if the section it refers to was removed. */
	if (s->st_shndx != SHN_UNDEF && s->st_shndx < SHN_LORESERVE &&
	    ecp->secndx[s->st_shndx] == 0)
		return (1);

	/* Keep the symbol if specified by command line option -K. */
	if (lookup_symop_list(ecp, name, SYMOP_KEEP) != NULL)
		return (0);

	if (ecp->strip == STRIP_ALL)
		return (1);

	/* Mark symbols used in relocation. */
	if (ecp->v_rel == NULL)
		mark_reloc_symbols(ecp, sc);

	/* Mark symbols used in section groups. */
	if (ecp->v_grp == NULL)
		mark_section_group_symbols(ecp, sc);

	/*
	 * Strip the symbol if specified by command line option -N,
	 * unless it's used in relocation.
	 */
	if (lookup_symop_list(ecp, name, SYMOP_STRIP) != NULL) {
		if (BIT_ISSET(ecp->v_rel, i)) {
			warnx("not stripping symbol `%s' because it is named"
			    " in a relocation", name);
			return (0);
		}
		return (1);
	}

	if (is_needed_symbol(ecp, i, s))
		return (0);

	if (ecp->strip == STRIP_UNNEEDED)
		return (1);

	if ((ecp->flags & DISCARD_LOCAL) && is_local_symbol(s->st_info) &&
	    !is_debug_symbol(s->st_info))
		return (1);

	if ((ecp->flags & DISCARD_LLABEL) && is_local_symbol(s->st_info) &&
	    !is_debug_symbol(s->st_info) && is_local_label(name))
		return (1);

	if (ecp->strip == STRIP_DEBUG && is_debug_symbol(s->st_info))
		return (1);

	return (0);
}