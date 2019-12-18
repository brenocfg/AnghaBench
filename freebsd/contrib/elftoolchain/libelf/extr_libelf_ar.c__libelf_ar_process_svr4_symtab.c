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
typedef  size_t uint32_t ;
typedef  void* off_t ;
struct TYPE_9__ {size_t e_rawsymtabsz; size_t e_symtabsz; TYPE_3__* e_symtab; scalar_t__ e_rawsymtab; } ;
struct TYPE_10__ {TYPE_1__ e_ar; } ;
struct TYPE_12__ {size_t e_rawsize; TYPE_2__ e_u; } ;
struct TYPE_11__ {unsigned long as_hash; char* as_name; void* as_off; } ;
typedef  TYPE_3__ Elf_Arsym ;
typedef  TYPE_4__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE ; 
 int /*<<< orphan*/  GET_WORD (unsigned char*,size_t) ; 
 size_t INTSZ ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESOURCE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 unsigned long elf_hash (char*) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 TYPE_3__* malloc (int) ; 

Elf_Arsym *
_libelf_ar_process_svr4_symtab(Elf *e, size_t *count)
{
	uint32_t off;
	size_t n, nentries;
	Elf_Arsym *symtab, *sym;
	unsigned char *p, *s, *end;

	assert(e != NULL);
	assert(count != NULL);
	assert(e->e_u.e_ar.e_symtab == NULL);

	symtab = NULL;

	if (e->e_u.e_ar.e_rawsymtabsz < INTSZ)
		goto symtaberror;

	p = (unsigned char *) e->e_u.e_ar.e_rawsymtab;
	end = p + e->e_u.e_ar.e_rawsymtabsz;

	GET_WORD(p, nentries);
	p += INTSZ;

	if (nentries == 0 || p + nentries * INTSZ >= end)
		goto symtaberror;

	/* Allocate space for a nentries + a sentinel. */
	if ((symtab = malloc(sizeof(Elf_Arsym) * (nentries+1))) == NULL) {
		LIBELF_SET_ERROR(RESOURCE, 0);
		return (NULL);
	}

	s = p + (nentries * INTSZ); /* start of the string table. */

	for (n = nentries, sym = symtab; n > 0; n--) {
		if (s >= end)
			goto symtaberror;

		GET_WORD(p, off);
		if (off >= e->e_rawsize)
			goto symtaberror;

		sym->as_off = (off_t) off;
		sym->as_hash = elf_hash((char *) s);
		sym->as_name = (char *) s;

		p += INTSZ;
		sym++;

		for (; s < end && *s++ != '\0';) /* skip to next string */
			;
	}

	/* Fill up the sentinel entry. */
	sym->as_name = NULL;
	sym->as_hash = ~0UL;
	sym->as_off = (off_t) 0;

	*count = e->e_u.e_ar.e_symtabsz = nentries + 1;
	e->e_u.e_ar.e_symtab = symtab;

	return (symtab);

symtaberror:
	if (symtab)
		free(symtab);
	LIBELF_SET_ERROR(ARCHIVE, 0);
	return (NULL);
}