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
struct section {scalar_t__ type; size_t off; int /*<<< orphan*/  scn; } ;
struct TYPE_7__ {scalar_t__ e_type; } ;
struct readelf {size_t shnum; struct section* sl; int /*<<< orphan*/  elf; TYPE_1__ ehdr; } ;
struct TYPE_9__ {char const* d_buf; size_t d_size; } ;
struct TYPE_8__ {scalar_t__ p_type; size_t p_offset; size_t p_filesz; } ;
typedef  TYPE_2__ GElf_Phdr ;
typedef  TYPE_3__ Elf_Data ;

/* Variables and functions */
 scalar_t__ ET_CORE ; 
 scalar_t__ PT_NOTE ; 
 scalar_t__ SHT_NOTE ; 
 int /*<<< orphan*/  dump_notes_content (struct readelf*,char const*,size_t,size_t) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int elf_errno () ; 
 TYPE_3__* elf_getdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ elf_getphnum (int /*<<< orphan*/ ,size_t*) ; 
 char* elf_rawfile (int /*<<< orphan*/ ,size_t*) ; 
 TYPE_2__* gelf_getphdr (int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static void
dump_notes(struct readelf *re)
{
	struct section *s;
	const char *rawfile;
	GElf_Phdr phdr;
	Elf_Data *d;
	size_t filesize, phnum;
	int i, elferr;

	if (re->ehdr.e_type == ET_CORE) {
		/*
		 * Search program headers in the core file for
		 * PT_NOTE entry.
		 */
		if (elf_getphnum(re->elf, &phnum) == 0) {
			warnx("elf_getphnum failed: %s", elf_errmsg(-1));
			return;
		}
		if (phnum == 0)
			return;
		if ((rawfile = elf_rawfile(re->elf, &filesize)) == NULL) {
			warnx("elf_rawfile failed: %s", elf_errmsg(-1));
			return;
		}
		for (i = 0; (size_t) i < phnum; i++) {
			if (gelf_getphdr(re->elf, i, &phdr) != &phdr) {
				warnx("gelf_getphdr failed: %s",
				    elf_errmsg(-1));
				continue;
			}
			if (phdr.p_type == PT_NOTE) {
				if (phdr.p_offset >= filesize ||
				    phdr.p_filesz > filesize - phdr.p_offset) {
					warnx("invalid PHDR offset");
					continue;
				}
				dump_notes_content(re, rawfile + phdr.p_offset,
				    phdr.p_filesz, phdr.p_offset);
			}
		}

	} else {
		/*
		 * For objects other than core files, Search for
		 * SHT_NOTE sections.
		 */
		for (i = 0; (size_t) i < re->shnum; i++) {
			s = &re->sl[i];
			if (s->type == SHT_NOTE) {
				(void) elf_errno();
				if ((d = elf_getdata(s->scn, NULL)) == NULL) {
					elferr = elf_errno();
					if (elferr != 0)
						warnx("elf_getdata failed: %s",
						    elf_errmsg(elferr));
					continue;
				}
				dump_notes_content(re, d->d_buf, d->d_size,
				    s->off);
			}
		}
	}
}