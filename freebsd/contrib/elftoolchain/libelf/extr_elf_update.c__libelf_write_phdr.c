#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
struct _Elf_Extent {scalar_t__ ex_type; size_t ex_start; } ;
typedef  int /*<<< orphan*/  src ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  dst ;
struct TYPE_14__ {size_t e_nphdr; } ;
struct TYPE_15__ {TYPE_1__ e_elf; } ;
struct TYPE_19__ {int e_class; int /*<<< orphan*/  e_byteorder; int /*<<< orphan*/  e_version; TYPE_2__ e_u; } ;
struct TYPE_18__ {scalar_t__ e_phoff; } ;
struct TYPE_17__ {size_t e_phoff; } ;
struct TYPE_16__ {unsigned char* d_buf; size_t d_size; int /*<<< orphan*/  d_type; int /*<<< orphan*/  d_version; } ;
typedef  TYPE_3__ Elf_Data ;
typedef  TYPE_4__ Elf64_Ehdr ;
typedef  TYPE_5__ Elf32_Ehdr ;
typedef  TYPE_6__ Elf ;

/* Variables and functions */
 int ELFCLASS32 ; 
 scalar_t__ ELF_EXTENT_PHDR ; 
 int /*<<< orphan*/  ELF_TOFILE ; 
 int /*<<< orphan*/  ELF_T_PHDR ; 
 void* _libelf_ehdr (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int _libelf_elfmachine (TYPE_6__*) ; 
 size_t _libelf_falign (int /*<<< orphan*/ ,int) ; 
 size_t _libelf_fsize (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t) ; 
 unsigned char* _libelf_getphdr (TYPE_6__*,int) ; 
 size_t _libelf_msize (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _libelf_xlate (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static off_t
_libelf_write_phdr(Elf *e, unsigned char *nf, struct _Elf_Extent *ex)
{
	int ec, em;
	void *ehdr;
	Elf32_Ehdr *eh32;
	Elf64_Ehdr *eh64;
	Elf_Data dst, src;
	size_t fsz, phnum;
	uint64_t phoff;

	assert(ex->ex_type == ELF_EXTENT_PHDR);

	ec = e->e_class;
	ehdr = _libelf_ehdr(e, ec, 0);
	phnum = e->e_u.e_elf.e_nphdr;

	assert(phnum > 0);

	if (ec == ELFCLASS32) {
		eh32 = (Elf32_Ehdr *) ehdr;
		phoff = (uint64_t) eh32->e_phoff;
	} else {
		eh64 = (Elf64_Ehdr *) ehdr;
		phoff = eh64->e_phoff;
	}

	em = _libelf_elfmachine(e);

	assert(phoff > 0);
	assert(ex->ex_start == phoff);
	assert(phoff % _libelf_falign(ELF_T_PHDR, ec) == 0);

	(void) memset(&dst, 0, sizeof(dst));
	(void) memset(&src, 0, sizeof(src));

	fsz = _libelf_fsize(ELF_T_PHDR, ec, e->e_version, phnum);
	assert(fsz > 0);

	src.d_buf = _libelf_getphdr(e, ec);
	src.d_version = dst.d_version = e->e_version;
	src.d_type = ELF_T_PHDR;
	src.d_size = phnum * _libelf_msize(ELF_T_PHDR, ec,
	    e->e_version);

	dst.d_size = fsz;
	dst.d_buf = nf + ex->ex_start;

	if (_libelf_xlate(&dst, &src, e->e_byteorder, ec, em, ELF_TOFILE) ==
	    NULL)
		return ((off_t) -1);

	return ((off_t) (phoff + fsz));
}