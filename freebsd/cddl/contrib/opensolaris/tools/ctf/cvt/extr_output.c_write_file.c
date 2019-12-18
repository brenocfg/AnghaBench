#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  size_t off_t ;
typedef  TYPE_1__* caddr_t ;
struct TYPE_25__ {int e_phnum; int e_shnum; int e_shstrndx; size_t e_shoff; scalar_t__ e_phoff; } ;
struct TYPE_24__ {size_t sh_name; scalar_t__ sh_type; size_t sh_addralign; size_t sh_offset; int sh_link; int sh_info; char sh_size; int sh_entsize; } ;
struct TYPE_23__ {size_t st_shndx; } ;
struct TYPE_22__ {int d_align; char d_size; scalar_t__ d_off; struct TYPE_22__* d_buf; int /*<<< orphan*/  d_version; int /*<<< orphan*/  d_type; } ;
typedef  scalar_t__ GElf_Word ;
typedef  TYPE_2__ GElf_Sym ;
typedef  TYPE_3__ GElf_Shdr ;
typedef  int /*<<< orphan*/  GElf_Phdr ;
typedef  TYPE_4__ GElf_Ehdr ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  TYPE_1__ Elf_Data ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 char* CTF_ELF_SCN_NAME ; 
 int CTF_KEEP_STABS ; 
 int CTF_USE_DYNSYM ; 
 int /*<<< orphan*/  ELF_C_SET ; 
 int /*<<< orphan*/  ELF_C_WRITE ; 
 int /*<<< orphan*/  ELF_F_LAYOUT ; 
 int /*<<< orphan*/  ELF_T_ADDR ; 
 int /*<<< orphan*/  EV_CURRENT ; 
 size_t SHN_LORESERVE ; 
 scalar_t__ SHT_DYNSYM ; 
 scalar_t__ SHT_NOBITS ; 
 scalar_t__ SHT_PROGBITS ; 
 scalar_t__ SHT_REL ; 
 scalar_t__ SHT_RELA ; 
 scalar_t__ SHT_SYMTAB ; 
 int /*<<< orphan*/  bcopy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  elf_flagelf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* elf_getdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * elf_getscn (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* elf_newdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * elf_newscn (int /*<<< orphan*/ *) ; 
 char* elf_strptr (int /*<<< orphan*/ *,int,size_t) ; 
 scalar_t__ elf_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elfterminate (char const*,char*,...) ; 
 int /*<<< orphan*/  free (int*) ; 
 size_t gelf_fsize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gelf_getclass (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gelf_getehdr (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  gelf_getphdr (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gelf_getshdr (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * gelf_getsym (TYPE_1__*,int,TYPE_2__*) ; 
 int /*<<< orphan*/ * gelf_newehdr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gelf_newphdr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gelf_update_ehdr (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  gelf_update_phdr (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ gelf_update_shdr (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  gelf_update_sym (TYPE_1__*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (TYPE_1__*,char*) ; 
 char strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  terminate (char*,char const*,char*) ; 
 void* xmalloc (char) ; 

__attribute__((used)) static void
write_file(Elf *src, const char *srcname, Elf *dst, const char *dstname,
    caddr_t ctfdata, size_t ctfsize, int flags)
{
	GElf_Ehdr sehdr, dehdr;
	Elf_Scn *sscn, *dscn;
	Elf_Data *sdata, *ddata;
	GElf_Shdr shdr;
	GElf_Word symtab_type;
	int symtab_idx = -1;
	off_t new_offset = 0;
	off_t ctfnameoff = 0;
	int dynsym = (flags & CTF_USE_DYNSYM);
	int keep_stabs = (flags & CTF_KEEP_STABS);
	int *secxlate;
	int srcidx, dstidx;
	int curnmoff = 0;
	int changing = 0;
	int pad;
	int i;

	if (gelf_newehdr(dst, gelf_getclass(src)) == NULL)
		elfterminate(dstname, "Cannot copy ehdr to temp file");
	gelf_getehdr(src, &sehdr);
	memcpy(&dehdr, &sehdr, sizeof (GElf_Ehdr));
	gelf_update_ehdr(dst, &dehdr);

	symtab_type = dynsym ? SHT_DYNSYM : SHT_SYMTAB;

	/*
	 * Neither the existing stab sections nor the SUNW_ctf sections (new or
	 * existing) are SHF_ALLOC'd, so they won't be in areas referenced by
	 * program headers.  As such, we can just blindly copy the program
	 * headers from the existing file to the new file.
	 */
	if (sehdr.e_phnum != 0) {
		(void) elf_flagelf(dst, ELF_C_SET, ELF_F_LAYOUT);
		if (gelf_newphdr(dst, sehdr.e_phnum) == NULL)
			elfterminate(dstname, "Cannot make phdrs in temp file");

		for (i = 0; i < sehdr.e_phnum; i++) {
			GElf_Phdr phdr;

			gelf_getphdr(src, i, &phdr);
			gelf_update_phdr(dst, i, &phdr);
		}
	}

	secxlate = xmalloc(sizeof (int) * sehdr.e_shnum);
	for (srcidx = dstidx = 0; srcidx < sehdr.e_shnum; srcidx++) {
		Elf_Scn *scn = elf_getscn(src, srcidx);
		GElf_Shdr shdr1;
		char *sname;

		gelf_getshdr(scn, &shdr1);
		sname = elf_strptr(src, sehdr.e_shstrndx, shdr1.sh_name);
		if (sname == NULL) {
			elfterminate(srcname, "Can't find string at %u",
			    shdr1.sh_name);
		}

		if (strcmp(sname, CTF_ELF_SCN_NAME) == 0) {
			secxlate[srcidx] = -1;
		} else if (!keep_stabs &&
		    (strncmp(sname, ".stab", 5) == 0 ||
		    strncmp(sname, ".debug", 6) == 0 ||
		    strncmp(sname, ".rel.debug", 10) == 0 ||
		    strncmp(sname, ".rela.debug", 11) == 0)) {
			secxlate[srcidx] = -1;
		} else if (dynsym && shdr1.sh_type == SHT_SYMTAB) {
			/*
			 * If we're building CTF against the dynsym,
			 * we'll rip out the symtab so debuggers aren't
			 * confused.
			 */
			secxlate[srcidx] = -1;
		} else {
			secxlate[srcidx] = dstidx++;
			curnmoff += strlen(sname) + 1;
		}

		new_offset = (off_t)dehdr.e_phoff;
	}

	for (srcidx = 1; srcidx < sehdr.e_shnum; srcidx++) {
		char *sname;

		sscn = elf_getscn(src, srcidx);
		gelf_getshdr(sscn, &shdr);

		if (secxlate[srcidx] == -1) {
			changing = 1;
			continue;
		}

		dscn = elf_newscn(dst);

		/*
		 * If this file has program headers, we need to explicitly lay
		 * out sections.  If none of the sections prior to this one have
		 * been removed, then we can just use the existing location.  If
		 * one or more sections have been changed, then we need to
		 * adjust this one to avoid holes.
		 */
		if (changing && sehdr.e_phnum != 0) {
			pad = new_offset % shdr.sh_addralign;

			if (pad)
				new_offset += shdr.sh_addralign - pad;
			shdr.sh_offset = new_offset;
		}

		shdr.sh_link = secxlate[shdr.sh_link];

		if (shdr.sh_type == SHT_REL || shdr.sh_type == SHT_RELA)
			shdr.sh_info = secxlate[shdr.sh_info];

		sname = elf_strptr(src, sehdr.e_shstrndx, shdr.sh_name);
		if (sname == NULL) {
			elfterminate(srcname, "Can't find string at %u",
			    shdr.sh_name);
		}

#ifndef illumos
		if (gelf_update_shdr(dscn, &shdr) == 0)
			elfterminate(dstname, "Cannot update sect %s", sname);
#endif

		if ((sdata = elf_getdata(sscn, NULL)) == NULL)
			elfterminate(srcname, "Cannot get sect %s data", sname);
		if ((ddata = elf_newdata(dscn)) == NULL)
			elfterminate(dstname, "Can't make sect %s data", sname);
#ifdef illumos
		bcopy(sdata, ddata, sizeof (Elf_Data));
#else
		/*
		 * FreeBSD's Elf_Data has private fields which the
		 * elf_* routines manage. Simply copying the 
		 * entire structure corrupts the data. So we need
		 * to copy the public fields explictly.
		 */
		ddata->d_align = sdata->d_align;
		ddata->d_off = sdata->d_off;
		ddata->d_size = sdata->d_size;
		ddata->d_type = sdata->d_type;
		ddata->d_version = sdata->d_version;
#endif

		if (srcidx == sehdr.e_shstrndx) {
			char seclen = strlen(CTF_ELF_SCN_NAME);

			ddata->d_buf = xmalloc(ddata->d_size + shdr.sh_size +
			    seclen + 1);
			bcopy(sdata->d_buf, ddata->d_buf, shdr.sh_size);
			strcpy((caddr_t)ddata->d_buf + shdr.sh_size,
			    CTF_ELF_SCN_NAME);
			ctfnameoff = (off_t)shdr.sh_size;
			shdr.sh_size += seclen + 1;
			ddata->d_size += seclen + 1;

			if (sehdr.e_phnum != 0)
				changing = 1;
		}

		if (shdr.sh_type == symtab_type && shdr.sh_entsize != 0) {
			int nsym = shdr.sh_size / shdr.sh_entsize;

			symtab_idx = secxlate[srcidx];

			ddata->d_buf = xmalloc(shdr.sh_size);
			bcopy(sdata->d_buf, ddata->d_buf, shdr.sh_size);

			for (i = 0; i < nsym; i++) {
				GElf_Sym sym;
				short newscn;

				if (gelf_getsym(ddata, i, &sym) == NULL)
					printf("Could not get symbol %d\n",i);

				if (sym.st_shndx >= SHN_LORESERVE)
					continue;

				if ((newscn = secxlate[sym.st_shndx]) !=
				    sym.st_shndx) {
					sym.st_shndx =
					    (newscn == -1 ? 1 : newscn);

					gelf_update_sym(ddata, i, &sym);
				}
			}
		}

#ifndef illumos
		if (ddata->d_buf == NULL && sdata->d_buf != NULL) {
			ddata->d_buf = xmalloc(shdr.sh_size);
			bcopy(sdata->d_buf, ddata->d_buf, shdr.sh_size);
		}
#endif

		if (gelf_update_shdr(dscn, &shdr) == 0)
			elfterminate(dstname, "Cannot update sect %s", sname);

		new_offset = (off_t)shdr.sh_offset;
		if (shdr.sh_type != SHT_NOBITS)
			new_offset += shdr.sh_size;
	}

	if (symtab_idx == -1) {
		terminate("%s: Cannot find %s section\n", srcname,
		    dynsym ? "SHT_DYNSYM" : "SHT_SYMTAB");
	}

	/* Add the ctf section */
	dscn = elf_newscn(dst);
	gelf_getshdr(dscn, &shdr);
	shdr.sh_name = ctfnameoff;
	shdr.sh_type = SHT_PROGBITS;
	shdr.sh_size = ctfsize;
	shdr.sh_link = symtab_idx;
	shdr.sh_addralign = 4;
	if (changing && sehdr.e_phnum != 0) {
		pad = new_offset % shdr.sh_addralign;

		if (pad)
			new_offset += shdr.sh_addralign - pad;

		shdr.sh_offset = new_offset;
		new_offset += shdr.sh_size;
	}

	ddata = elf_newdata(dscn);
	ddata->d_buf = ctfdata;
	ddata->d_size = ctfsize;
	ddata->d_align = shdr.sh_addralign;
	ddata->d_off = 0;

	gelf_update_shdr(dscn, &shdr);

	/* update the section header location */
	if (sehdr.e_phnum != 0) {
		size_t align = gelf_fsize(dst, ELF_T_ADDR, 1, EV_CURRENT);
		size_t r = new_offset % align;

		if (r)
			new_offset += align - r;

		dehdr.e_shoff = new_offset;
	}

	/* commit to disk */
	dehdr.e_shstrndx = secxlate[sehdr.e_shstrndx];
	gelf_update_ehdr(dst, &dehdr);
	if (elf_update(dst, ELF_C_WRITE) < 0)
		elfterminate(dstname, "Cannot finalize temp file");

	free(secxlate);
}