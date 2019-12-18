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
struct ar_hdr {scalar_t__ ar_name; } ;
struct TYPE_5__ {size_t e_rawstrtabsz; unsigned char* e_rawstrtab; } ;
struct TYPE_6__ {TYPE_1__ e_ar; } ;
struct TYPE_7__ {scalar_t__ e_kind; unsigned char const* e_rawfile; int e_rawsize; TYPE_2__ e_u; } ;
typedef  TYPE_3__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE ; 
 scalar_t__ ELF_K_AR ; 
 scalar_t__ IS_EXTENDED_BSD_NAME (unsigned char const*) ; 
 size_t LIBELF_AR_BSD_EXTENDED_NAME_PREFIX_SIZE ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESOURCE ; 
 scalar_t__ _libelf_ar_get_number (char const*,size_t const,int,size_t*) ; 
 int /*<<< orphan*/  assert (int) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

char *
_libelf_ar_get_translated_name(const struct ar_hdr *arh, Elf *ar)
{
	char *s;
	unsigned char c;
	size_t len, offset;
	const unsigned char *buf, *p, *q, *r;
	const size_t bufsize = sizeof(arh->ar_name);

	assert(arh != NULL);
	assert(ar->e_kind == ELF_K_AR);
	assert((const unsigned char *) arh >= ar->e_rawfile &&
	    (const unsigned char *) arh < ar->e_rawfile + ar->e_rawsize);

	buf = (const unsigned char *) arh->ar_name;

	/*
	 * Check for extended naming.
	 *
	 * If the name matches the pattern "^/[0-9]+", it is an
	 * SVR4-style extended name.  If the name matches the pattern
	 * "#1/[0-9]+", the entry uses BSD style extended naming.
	 */
	if (buf[0] == '/' && (c = buf[1]) >= '0' && c <= '9') {
		/*
		 * The value in field ar_name is a decimal offset into
		 * the archive string table where the actual name
		 * resides.
		 */
		if (_libelf_ar_get_number((const char *) (buf + 1),
			bufsize - 1, 10, &offset) == 0) {
			LIBELF_SET_ERROR(ARCHIVE, 0);
			return (NULL);
		}

		if (offset > ar->e_u.e_ar.e_rawstrtabsz) {
			LIBELF_SET_ERROR(ARCHIVE, 0);
			return (NULL);
		}

		p = q = ar->e_u.e_ar.e_rawstrtab + offset;
		r = ar->e_u.e_ar.e_rawstrtab + ar->e_u.e_ar.e_rawstrtabsz;

		for (; p < r && *p != '/'; p++)
			;
		len = (size_t) (p - q + 1); /* space for the trailing NUL */

		if ((s = malloc(len)) == NULL) {
			LIBELF_SET_ERROR(RESOURCE, 0);
			return (NULL);
		}

		(void) strncpy(s, (const char *) q, len - 1);
		s[len - 1] = '\0';

		return (s);
	} else if (IS_EXTENDED_BSD_NAME(buf)) {
		r = buf + LIBELF_AR_BSD_EXTENDED_NAME_PREFIX_SIZE;

		if (_libelf_ar_get_number((const char *) r, bufsize -
			LIBELF_AR_BSD_EXTENDED_NAME_PREFIX_SIZE, 10,
			&len) == 0) {
			LIBELF_SET_ERROR(ARCHIVE, 0);
			return (NULL);
		}

		/*
		 * Allocate space for the file name plus a
		 * trailing NUL.
		 */
		if ((s = malloc(len + 1)) == NULL) {
			LIBELF_SET_ERROR(RESOURCE, 0);
			return (NULL);
		}

		/*
		 * The file name follows the archive header.
		 */
		q = (const unsigned char *) (arh + 1);

		(void) strncpy(s, (const char *) q, len);
		s[len] = '\0';

		return (s);
	}

	/*
	 * A 'normal' name.
	 *
	 * Skip back over trailing blanks from the end of the field.
	 * In the SVR4 format, a '/' is used as a terminator for
	 * non-special names.
	 */
	for (q = buf + bufsize - 1; q >= buf && *q == ' '; --q)
		;

	if (q >= buf) {
		if (*q == '/') {
			/*
			 * SVR4 style names: ignore the trailing
			 * character '/', but only if the name is not
			 * one of the special names "/" and "//".
			 */
			if (q > buf + 1 ||
			    (q == (buf + 1) && *buf != '/'))
				q--;
		}

		len = (size_t) (q - buf + 2); /* Space for a trailing NUL. */
	} else {
		/* The buffer only had blanks. */
		buf = (const unsigned char *) "";
		len = 1;
	}

	if ((s = malloc(len)) == NULL) {
		LIBELF_SET_ERROR(RESOURCE, 0);
		return (NULL);
	}

	(void) strncpy(s, (const char *) buf, len - 1);
	s[len - 1] = '\0';

	return (s);
}