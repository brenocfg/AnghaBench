#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct _Elf_Extent {scalar_t__ ex_type; scalar_t__ ex_start; } ;
typedef  int /*<<< orphan*/  src ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  dst ;
struct TYPE_10__ {int e_class; int /*<<< orphan*/  e_byteorder; int /*<<< orphan*/  e_version; } ;
struct TYPE_9__ {unsigned char* d_buf; size_t d_size; int /*<<< orphan*/  d_version; int /*<<< orphan*/  d_type; } ;
typedef  TYPE_1__ Elf_Data ;
typedef  TYPE_2__ Elf ;

/* Variables and functions */
 scalar_t__ ELF_EXTENT_EHDR ; 
 int /*<<< orphan*/  ELF_TOFILE ; 
 int /*<<< orphan*/  ELF_T_EHDR ; 
 void* _libelf_ehdr (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int _libelf_elfmachine (TYPE_2__*) ; 
 size_t _libelf_fsize (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t) ; 
 size_t _libelf_msize (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _libelf_xlate (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static off_t
_libelf_write_ehdr(Elf *e, unsigned char *nf, struct _Elf_Extent *ex)
{
	int ec, em;
	void *ehdr;
	size_t fsz, msz;
	Elf_Data dst, src;

	assert(ex->ex_type == ELF_EXTENT_EHDR);
	assert(ex->ex_start == 0); /* Ehdr always comes first. */

	ec = e->e_class;

	ehdr = _libelf_ehdr(e, ec, 0);
	assert(ehdr != NULL);

	fsz = _libelf_fsize(ELF_T_EHDR, ec, e->e_version, (size_t) 1);
	msz = _libelf_msize(ELF_T_EHDR, ec, e->e_version);

	em = _libelf_elfmachine(e);

	(void) memset(&dst, 0, sizeof(dst));
	(void) memset(&src, 0, sizeof(src));

	src.d_buf     = ehdr;
	src.d_size    = msz;
	src.d_type    = ELF_T_EHDR;
	src.d_version = dst.d_version = e->e_version;

	dst.d_buf     = nf;
	dst.d_size    = fsz;

	if (_libelf_xlate(&dst, &src, e->e_byteorder, ec, em, ELF_TOFILE) ==
	    NULL)
		return ((off_t) -1);

	return ((off_t) fsz);
}