#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct section {scalar_t__ type; scalar_t__ name; int /*<<< orphan*/  scn; } ;
struct TYPE_5__ {scalar_t__* e_ident; } ;
struct elfdump {size_t shnum; int flags; TYPE_1__ ehdr; int /*<<< orphan*/  snl; struct section* sl; } ;
typedef  int /*<<< orphan*/  idx ;
struct TYPE_7__ {size_t d_size; scalar_t__* d_buf; } ;
struct TYPE_6__ {scalar_t__ n_namesz; scalar_t__ n_descsz; scalar_t__ n_type; } ;
typedef  TYPE_2__ Elf_Note ;
typedef  TYPE_3__ Elf_Data ;

/* Variables and functions */
 size_t EI_DATA ; 
 scalar_t__ ELFDATA2MSB ; 
 int /*<<< orphan*/  PRT (char*,...) ; 
 scalar_t__ SHT_NOTE ; 
 int SOLARIS_FMT ; 
 scalar_t__ STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ be32dec (scalar_t__*) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 TYPE_3__* elf_getdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ find_name (struct elfdump*,scalar_t__) ; 
 scalar_t__ le32dec (scalar_t__*) ; 
 size_t roundup2 (scalar_t__,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static void
elf_print_note(struct elfdump *ed)
{
	struct section	*s;
	Elf_Data        *data;
	Elf_Note	*en;
	uint32_t	 namesz;
	uint32_t	 descsz;
	uint32_t	 desc;
	size_t		 count;
	int		 elferr, i;
	uint8_t		*src;
	char		 idx[17];

	s = NULL;
	for (i = 0; (size_t)i < ed->shnum; i++) {
		s = &ed->sl[i];
		if (s->type == SHT_NOTE && s->name &&
		    !strcmp(s->name, ".note.ABI-tag") &&
		    (STAILQ_EMPTY(&ed->snl) || find_name(ed, s->name)))
			break;
	}
	if ((size_t)i >= ed->shnum)
		return;
	if (ed->flags & SOLARIS_FMT)
		PRT("\nNote Section:  %s\n", s->name);
	else
		PRT("\nnote (%s):\n", s->name);
	(void) elf_errno();
	if ((data = elf_getdata(s->scn, NULL)) == NULL) {
		elferr = elf_errno();
		if (elferr != 0)
			warnx("elf_getdata failed: %s", elf_errmsg(elferr));
		return;
	}
	src = data->d_buf;
	count = data->d_size;
	while (count > sizeof(Elf_Note)) {
		en = (Elf_Note *) (uintptr_t) src;
		namesz = en->n_namesz;
		descsz = en->n_descsz;
		src += sizeof(Elf_Note);
		count -= sizeof(Elf_Note);
		if (roundup2(namesz, 4) + roundup2(descsz, 4) > count) {
			warnx("truncated note section");
			return;
		}
		if (ed->flags & SOLARIS_FMT) {
			PRT("\n    type   %#x\n", en->n_type);
			PRT("    namesz %#x:\n", en->n_namesz);
			PRT("%s\n", src);
		} else
			PRT("\t%s ", src);
		src += roundup2(namesz, 4);
		count -= roundup2(namesz, 4);

		/*
		 * Note that we dump the whole desc part if we're in
		 * "Solaris mode", while in the normal mode, we only look
		 * at the first 4 bytes (a 32bit word) of the desc, i.e,
		 * we assume that it's always a FreeBSD version number.
		 */
		if (ed->flags & SOLARIS_FMT) {
			PRT("    descsz %#x:", en->n_descsz);
			for (i = 0; (uint32_t)i < descsz; i++) {
				if ((i & 0xF) == 0) {
					snprintf(idx, sizeof(idx), "desc[%d]",
					    i);
					PRT("\n      %-9s", idx);
				} else if ((i & 0x3) == 0)
					PRT("  ");
				PRT(" %2.2x", src[i]);
			}
			PRT("\n");
		} else {
			if (ed->ehdr.e_ident[EI_DATA] == ELFDATA2MSB)
				desc = be32dec(src);
			else
				desc = le32dec(src);
			PRT("%d\n", desc);
		}
		src += roundup2(descsz, 4);
		count -= roundup2(descsz, 4);
	}
}