#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct stat {size_t st_size; } ;
struct elfcopy {int /*<<< orphan*/  v_arobj; int /*<<< orphan*/  rela_off; int /*<<< orphan*/ * eout; int /*<<< orphan*/ * ein; } ;
struct ar_obj {char* buf; size_t size; int /*<<< orphan*/  name; int /*<<< orphan*/ * maddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_C_READ ; 
 int /*<<< orphan*/  ELF_C_SET ; 
 int /*<<< orphan*/  ELF_C_WRITE ; 
 int /*<<< orphan*/  ELF_F_LAYOUT ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ar_obj*,int /*<<< orphan*/ ) ; 
 scalar_t__ _ARHDR_LEN ; 
 scalar_t__ _MAXNAMELEN_SVR4 ; 
 int /*<<< orphan*/  add_to_ar_str_table (struct elfcopy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  create_elf (struct elfcopy*) ; 
 int /*<<< orphan*/  create_tempfile (char**,int*) ; 
 void* elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int /*<<< orphan*/  elf_flagelf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_arsym (struct elfcopy*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fstat (int,struct stat*) ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  objs ; 
 scalar_t__ read (int,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ unlink (char*) ; 

__attribute__((used)) static void
process_ar_obj(struct elfcopy *ecp, struct ar_obj *obj)
{
	struct stat	 sb;
	char		*tempfile;
	int		 fd;

	/* Output to a temporary file. */
	create_tempfile(&tempfile, &fd);
	if ((ecp->eout = elf_begin(fd, ELF_C_WRITE, NULL)) == NULL)
		errx(EXIT_FAILURE, "elf_begin() failed: %s",
		    elf_errmsg(-1));
	elf_flagelf(ecp->eout, ELF_C_SET, ELF_F_LAYOUT);
	create_elf(ecp);
	elf_end(ecp->ein);
	elf_end(ecp->eout);
	free(obj->buf);
	obj->buf = NULL;

	/* Extract archive symbols. */
	if (lseek(fd, 0, SEEK_SET) < 0)
		err(EXIT_FAILURE, "lseek failed for '%s'", tempfile);
	if ((ecp->eout = elf_begin(fd, ELF_C_READ, NULL)) == NULL)
		errx(EXIT_FAILURE, "elf_begin() failed: %s",
		    elf_errmsg(-1));
	extract_arsym(ecp);
	elf_end(ecp->eout);

	if (fstat(fd, &sb) == -1)
		err(EXIT_FAILURE, "fstat %s failed", tempfile);
	if (lseek(fd, 0, SEEK_SET) < 0)
		err(EXIT_FAILURE, "lseek %s failed", tempfile);
	obj->size = sb.st_size;
	if ((obj->maddr = malloc(obj->size)) == NULL)
		err(EXIT_FAILURE, "memory allocation failed for '%s'",
		    tempfile);
	if ((size_t) read(fd, obj->maddr, obj->size) != obj->size)
		err(EXIT_FAILURE, "read failed for '%s'", tempfile);
	if (unlink(tempfile))
		err(EXIT_FAILURE, "unlink %s failed", tempfile);
	free(tempfile);
	close(fd);
	if (strlen(obj->name) > _MAXNAMELEN_SVR4)
		add_to_ar_str_table(ecp, obj->name);
	ecp->rela_off += _ARHDR_LEN + obj->size + obj->size % 2;
	STAILQ_INSERT_TAIL(&ecp->v_arobj, obj, objs);
}