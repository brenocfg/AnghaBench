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
struct stat {int st_nlink; int /*<<< orphan*/  st_mode; } ;
struct elfcopy {scalar_t__ itf; scalar_t__ otf; scalar_t__ oec; scalar_t__ oed; int flags; int /*<<< orphan*/ * ein; int /*<<< orphan*/ * eout; } ;

/* Variables and functions */
 scalar_t__ ELFCLASS64 ; 
 scalar_t__ ELFCLASSNONE ; 
 scalar_t__ ELFDATA2LSB ; 
 scalar_t__ ELFDATANONE ; 
 int /*<<< orphan*/  ELF_C_READ ; 
 int /*<<< orphan*/  ELF_C_SET ; 
 int /*<<< orphan*/  ELF_C_WRITE ; 
 int /*<<< orphan*/  ELF_F_LAYOUT ; 
#define  ELF_K_AR 135 
#define  ELF_K_ELF 134 
#define  ELF_K_NONE 133 
#define  ETF_BINARY 132 
#define  ETF_EFI 131 
 scalar_t__ ETF_ELF ; 
#define  ETF_IHEX 130 
#define  ETF_PE 129 
#define  ETF_SREC 128 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int O_CREAT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_RDWR ; 
 int PRESERVE_DATE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ac_create_ar (struct elfcopy*,int,int) ; 
 scalar_t__ ac_detect_ar (int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ copy_from_tempfile (char*,char const*,int,int*,int) ; 
 int /*<<< orphan*/  create_binary (int,int) ; 
 int /*<<< orphan*/  create_elf (struct elfcopy*) ; 
 int /*<<< orphan*/  create_elf_from_binary (struct elfcopy*,int,char const*) ; 
 int /*<<< orphan*/  create_elf_from_ihex (struct elfcopy*,int) ; 
 int /*<<< orphan*/  create_elf_from_srec (struct elfcopy*,int) ; 
 int /*<<< orphan*/  create_ihex (int,int) ; 
 int /*<<< orphan*/  create_pe (struct elfcopy*,int,int) ; 
 int /*<<< orphan*/  create_srec (struct elfcopy*,int,int,char const*) ; 
 int /*<<< orphan*/  create_tempfile (char**,int*) ; 
 void* elf_begin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 int /*<<< orphan*/  elf_flagelf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int elf_kind (int /*<<< orphan*/ *) ; 
 scalar_t__ elftc_set_timestamps (char const*,struct stat*) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int fchmod (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fstat (int,struct stat*) ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lstat (char const*,struct stat*) ; 
 int open (char const*,int,...) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ unlink (char*) ; 

__attribute__((used)) static void
create_file(struct elfcopy *ecp, const char *src, const char *dst)
{
	struct stat	 sb;
	char		*tempfile, *elftemp;
	int		 efd, ifd, ofd, ofd0, tfd;
	int		 in_place;

	tempfile = NULL;

	if (src == NULL)
		errx(EXIT_FAILURE, "internal: src == NULL");
	if ((ifd = open(src, O_RDONLY)) == -1)
		err(EXIT_FAILURE, "open %s failed", src);

	if (fstat(ifd, &sb) == -1)
		err(EXIT_FAILURE, "fstat %s failed", src);

	if (dst == NULL)
		create_tempfile(&tempfile, &ofd);
	else
		if ((ofd = open(dst, O_RDWR|O_CREAT, 0755)) == -1)
			err(EXIT_FAILURE, "open %s failed", dst);

#ifndef LIBELF_AR
	/* Detect and process ar(1) archive using libarchive. */
	if (ac_detect_ar(ifd)) {
		ac_create_ar(ecp, ifd, ofd);
		goto copy_done;
	}
#endif

	if (lseek(ifd, 0, SEEK_SET) < 0)
		err(EXIT_FAILURE, "lseek failed");

	/*
	 * If input object is not ELF file, convert it to an intermediate
	 * ELF object before processing.
	 */
	if (ecp->itf != ETF_ELF) {
		/*
		 * If the output object is not an ELF file, choose an arbitrary
		 * ELF format for the intermediate file. srec, ihex and binary
		 * formats are independent of class, endianness and machine
		 * type so these choices do not affect the output.
		 */
		if (ecp->otf != ETF_ELF) {
			if (ecp->oec == ELFCLASSNONE)
				ecp->oec = ELFCLASS64;
			if (ecp->oed == ELFDATANONE)
				ecp->oed = ELFDATA2LSB;
		}
		create_tempfile(&elftemp, &efd);
		if ((ecp->eout = elf_begin(efd, ELF_C_WRITE, NULL)) == NULL)
			errx(EXIT_FAILURE, "elf_begin() failed: %s",
			    elf_errmsg(-1));
		elf_flagelf(ecp->eout, ELF_C_SET, ELF_F_LAYOUT);
		if (ecp->itf == ETF_BINARY)
			create_elf_from_binary(ecp, ifd, src);
		else if (ecp->itf == ETF_IHEX)
			create_elf_from_ihex(ecp, ifd);
		else if (ecp->itf == ETF_SREC)
			create_elf_from_srec(ecp, ifd);
		else
			errx(EXIT_FAILURE, "Internal: invalid target flavour");
		elf_end(ecp->eout);

		/* Open intermediate ELF object as new input object. */
		close(ifd);
		if ((ifd = open(elftemp, O_RDONLY)) == -1)
			err(EXIT_FAILURE, "open %s failed", src);
		close(efd);
		if (unlink(elftemp) < 0)
			err(EXIT_FAILURE, "unlink %s failed", elftemp);
		free(elftemp);
	}

	if ((ecp->ein = elf_begin(ifd, ELF_C_READ, NULL)) == NULL)
		errx(EXIT_FAILURE, "elf_begin() failed: %s",
		    elf_errmsg(-1));

	switch (elf_kind(ecp->ein)) {
	case ELF_K_NONE:
		errx(EXIT_FAILURE, "file format not recognized");
	case ELF_K_ELF:
		if ((ecp->eout = elf_begin(ofd, ELF_C_WRITE, NULL)) == NULL)
			errx(EXIT_FAILURE, "elf_begin() failed: %s",
			    elf_errmsg(-1));

		/* elfcopy(1) manage ELF layout by itself. */
		elf_flagelf(ecp->eout, ELF_C_SET, ELF_F_LAYOUT);

		/*
		 * Create output ELF object.
		 */
		create_elf(ecp);
		elf_end(ecp->eout);

		/*
		 * Convert the output ELF object to binary/srec/ihex if need.
		 */
		if (ecp->otf != ETF_ELF) {
			/*
			 * Create (another) tempfile for binary/srec/ihex
			 * output object.
			 */
			if (tempfile != NULL) {
				if (unlink(tempfile) < 0)
					err(EXIT_FAILURE, "unlink %s failed",
					    tempfile);
				free(tempfile);
			}
			create_tempfile(&tempfile, &ofd0);


			/*
			 * Rewind the file descriptor being processed.
			 */
			if (lseek(ofd, 0, SEEK_SET) < 0)
				err(EXIT_FAILURE,
				    "lseek failed for the output object");

			/*
			 * Call flavour-specific conversion routine.
			 */
			switch (ecp->otf) {
			case ETF_BINARY:
				create_binary(ofd, ofd0);
				break;
			case ETF_IHEX:
				create_ihex(ofd, ofd0);
				break;
			case ETF_SREC:
				create_srec(ecp, ofd, ofd0,
				    dst != NULL ? dst : src);
				break;
			case ETF_PE:
			case ETF_EFI:
#if	WITH_PE
				create_pe(ecp, ofd, ofd0);
#else
				errx(EXIT_FAILURE, "PE/EFI support not enabled"
				    " at compile time");
#endif
				break;
			default:
				errx(EXIT_FAILURE, "Internal: unsupported"
				    " output flavour %d", ecp->oec);
			}

			close(ofd);
			ofd = ofd0;
		}

		break;

	case ELF_K_AR:
		/* XXX: Not yet supported. */
		break;
	default:
		errx(EXIT_FAILURE, "file format not supported");
	}

	elf_end(ecp->ein);

#ifndef LIBELF_AR
copy_done:
#endif

	if (tempfile != NULL) {
		in_place = 0;
		if (dst == NULL) {
			dst = src;
			if (lstat(dst, &sb) != -1 &&
			    (sb.st_nlink > 1 || S_ISLNK(sb.st_mode)))
				in_place = 1;
		}

		if (copy_from_tempfile(tempfile, dst, ofd, &tfd, in_place) < 0)
			err(EXIT_FAILURE, "creation of %s failed", dst);

		free(tempfile);
		tempfile = NULL;

		ofd = tfd;
	}

	if (strcmp(dst, "/dev/null") && fchmod(ofd, sb.st_mode) == -1)
		err(EXIT_FAILURE, "fchmod %s failed", dst);

	if ((ecp->flags & PRESERVE_DATE) &&
	    elftc_set_timestamps(dst, &sb) < 0)
		err(EXIT_FAILURE, "setting timestamps failed");

	close(ifd);
	close(ofd);
}