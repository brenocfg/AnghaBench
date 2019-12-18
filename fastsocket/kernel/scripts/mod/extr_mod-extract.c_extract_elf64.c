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
struct TYPE_7__ {size_t e_shstrndx; size_t e_shnum; int /*<<< orphan*/  e_shoff; } ;
struct TYPE_6__ {int /*<<< orphan*/  sh_addralign; int /*<<< orphan*/  sh_size; int /*<<< orphan*/  sh_flags; int /*<<< orphan*/  sh_type; int /*<<< orphan*/  sh_offset; int /*<<< orphan*/  sh_info; int /*<<< orphan*/  sh_name; } ;
typedef  size_t Elf64_Xword ;
typedef  size_t Elf64_Word ;
typedef  int /*<<< orphan*/  Elf64_Sym ;
typedef  TYPE_1__ Elf64_Shdr ;
typedef  int /*<<< orphan*/  Elf64_Rela ;
typedef  int /*<<< orphan*/  Elf64_Rel ;
typedef  size_t Elf64_Off ;
typedef  TYPE_2__ Elf64_Ehdr ;
typedef  int /*<<< orphan*/  Elf32_Word ;

/* Variables and functions */
 size_t SHF_ALLOC ; 
 size_t SHT_NOBITS ; 
 size_t SHT_REL ; 
 size_t SHT_RELA ; 
#define  SHT_STRTAB 129 
#define  SHT_SYMTAB 128 
 int* calloc (int,int) ; 
 int csum ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  extract_elf64_rel (void*,int,size_t,void*,size_t,int /*<<< orphan*/  const*,size_t,TYPE_1__*,int,int*,char const*,size_t,char const*) ; 
 int /*<<< orphan*/  extract_elf64_rela (void*,int,size_t,void*,size_t,int /*<<< orphan*/  const*,size_t,TYPE_1__*,int,int*,char const*,size_t,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int ftell (int /*<<< orphan*/ ) ; 
 size_t get16 (size_t*) ; 
 int get32 (int /*<<< orphan*/ *) ; 
 size_t get64 (int /*<<< orphan*/ *) ; 
 int is_verbose ; 
 int /*<<< orphan*/  outfd ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  set32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  verbose (char*,...) ; 
 int /*<<< orphan*/  write_out (void*,size_t) ; 
 int /*<<< orphan*/  write_out_val (int /*<<< orphan*/ ) ; 
 char const* xcsum ; 

__attribute__((used)) static void extract_elf64(void *buffer, size_t len, Elf64_Ehdr *hdr)
{
	const Elf64_Sym *symbols;
	Elf64_Shdr *sections;
	const char *secstrings, *strings;
	size_t nsyms, nstrings;
	int loop, shnum, *canonlist, *canonmap, canon, changed, tmp;

	sections = buffer + get64(&hdr->e_shoff);
	secstrings = buffer + get64(&sections[get16(&hdr->e_shstrndx)].sh_offset);
	shnum = get16(&hdr->e_shnum);

	/* find the symbol table and the string table and produce a list of
	 * index numbers of sections that contribute to the kernel's module
	 * image
	 */
	canonlist = calloc(sizeof(int), shnum * 2);
	if (!canonlist) {
		perror("calloc");
		exit(1);
	}
	canonmap = canonlist + shnum;
	canon = 0;

	symbols = NULL;
	strings = NULL;
	nstrings = 0;
	nsyms = 0;

	for (loop = 1; loop < shnum; loop++) {
		const char *sh_name = secstrings + get32(&sections[loop].sh_name);
		Elf64_Word  sh_type	= get32(&sections[loop].sh_type);
		Elf64_Xword sh_size	= get64(&sections[loop].sh_size);
		Elf64_Xword sh_flags	= get64(&sections[loop].sh_flags);
		Elf64_Word  sh_info	= get32(&sections[loop].sh_info);
		Elf64_Off   sh_offset	= get64(&sections[loop].sh_offset);
		void *data = buffer + sh_offset;

		/* quick sanity check */
		if (sh_type != SHT_NOBITS && len < sh_offset + sh_size) {
			fprintf(stderr, "Section goes beyond EOF\n");
			exit(3);
		}

		/* we only need to canonicalise allocatable sections */
		if (sh_flags & SHF_ALLOC)
			canonlist[canon++] = loop;
		else if ((sh_type == SHT_REL || sh_type == SHT_RELA) &&
			 get64(&sections[sh_info].sh_flags) & SHF_ALLOC)
			canonlist[canon++] = loop;

		/* keep track of certain special sections */
		switch (sh_type) {
		case SHT_SYMTAB:
			if (strcmp(sh_name, ".symtab") == 0) {
				symbols = data;
				nsyms = sh_size / sizeof(Elf64_Sym);
			}
			break;

		case SHT_STRTAB:
			if (strcmp(sh_name, ".strtab") == 0) {
				strings = data;
				nstrings = sh_size;
			}
			break;

		default:
			break;
		}
	}

	if (!symbols) {
		fprintf(stderr, "Couldn't locate symbol table\n");
		exit(3);
	}

	if (!strings) {
		fprintf(stderr, "Couldn't locate strings table\n");
		exit(3);
	}

	/* canonicalise the index numbers of the contributing section */
	do {
		changed = 0;

		for (loop = 0; loop < canon - 1; loop++) {
			const char *x = secstrings + get32(&sections[canonlist[loop + 0]].sh_name);
			const char *y = secstrings + get32(&sections[canonlist[loop + 1]].sh_name);
			if (strcmp(x, y) > 0) {
				tmp = canonlist[loop + 0];
				canonlist[loop + 0] = canonlist[loop + 1];
				canonlist[loop + 1] = tmp;
				changed = 1;
			}
		}

	} while (changed);

	for (loop = 0; loop < canon; loop++)
		canonmap[canonlist[loop]] = loop + 1;

	if (is_verbose > 1) {
		printf("\nSection canonicalisation map:\n");
		for (loop = 1; loop < shnum; loop++) {
			const char *x = secstrings + get32(&sections[loop].sh_name);
			printf("%4d %s\n", canonmap[loop], x);
		}

		printf("\nAllocated section list in canonical order:\n");
		for (loop = 0; loop < canon; loop++) {
			const char *x = secstrings + get32(&sections[canonlist[loop]].sh_name);
			printf("%4d %s\n", canonlist[loop], x);
		}
	}

	/* iterate through the section table looking for sections we want to
	 * contribute to the signature */
	verbose("\n");
	verbose("CAN FILE POS CS SECT NAME\n");
	verbose("=== ======== == ==== ==============================\n");

	for (loop = 0; loop < canon; loop++) {
		int sect = canonlist[loop];
		const char *sh_name = secstrings + get32(&sections[sect].sh_name);
		Elf64_Word  sh_type	= get32(&sections[sect].sh_type);
		Elf64_Xword sh_size	= get64(&sections[sect].sh_size);
		Elf64_Xword sh_flags	= get64(&sections[sect].sh_flags);
		Elf64_Word  sh_info	= get32(&sections[sect].sh_info);
		Elf64_Off   sh_offset	= get64(&sections[sect].sh_offset);
		void *data = buffer + sh_offset;

		csum = 0;

		/* include canonicalised relocation sections */
		if (sh_type == SHT_REL || sh_type == SHT_RELA) {
			Elf32_Word canon_sh_info;

			if (sh_info <= 0 && sh_info >= hdr->e_shnum) {
				fprintf(stderr,
					"Invalid ELF - REL/RELA sh_info does"
					" not refer to a valid section\n");
				exit(3);
			}

			verbose("%3u %08lx ", loop, ftell(outfd));

			set32(&canon_sh_info, canonmap[sh_info]);

			/* write out selected portions of the section header */
			write_out(sh_name, strlen(sh_name));
			write_out_val(sections[sect].sh_type);
			write_out_val(sections[sect].sh_flags);
			write_out_val(sections[sect].sh_size);
			write_out_val(sections[sect].sh_addralign);
			write_out_val(canon_sh_info);

			if (sh_type == SHT_RELA)
				extract_elf64_rela(buffer, sect, sh_info,
						   data, sh_size / sizeof(Elf64_Rela),
						   symbols, nsyms,
						   sections, shnum, canonmap,
						   strings, nstrings,
						   sh_name);
			else
				extract_elf64_rel(buffer, sect, sh_info,
						  data, sh_size / sizeof(Elf64_Rel),
						  symbols, nsyms,
						  sections, shnum, canonmap,
						  strings, nstrings,
						  sh_name);
			continue;
		}

		/* include the headers of BSS sections */
		if (sh_type == SHT_NOBITS && sh_flags & SHF_ALLOC) {
			verbose("%3u %08lx ", loop, ftell(outfd));

			/* write out selected portions of the section header */
			write_out(sh_name, strlen(sh_name));
			write_out_val(sections[sect].sh_type);
			write_out_val(sections[sect].sh_flags);
			write_out_val(sections[sect].sh_size);
			write_out_val(sections[sect].sh_addralign);

			verbose("%02x %4d %s\n", csum, sect, sh_name);
		}

		/* include allocatable loadable sections */
		if (sh_type != SHT_NOBITS && sh_flags & SHF_ALLOC)
			goto include_section;

		/* not this section */
		continue;

	include_section:
		verbose("%3u %08lx ", loop, ftell(outfd));

		/* write out selected portions of the section header */
		write_out(sh_name, strlen(sh_name));
		write_out_val(sections[sect].sh_type);
		write_out_val(sections[sect].sh_flags);
		write_out_val(sections[sect].sh_size);
		write_out_val(sections[sect].sh_addralign);

		/* write out the section data */
		write_out(data, sh_size);

		verbose("%02x %4d %s\n", csum, sect, sh_name);
	}

	verbose("%08lx         (%lu bytes csum 0x%02x)\n",
		ftell(outfd), ftell(outfd), xcsum);
}