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
struct elfcopy {int /*<<< orphan*/ * ein; scalar_t__ rela_off; } ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;
struct ar_obj {char* buf; int /*<<< orphan*/  mtime; int /*<<< orphan*/  md; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/ * name; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACV (int /*<<< orphan*/ ) ; 
 int ARCHIVE_EOF ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_RETRY ; 
 int ARCHIVE_WARN ; 
 scalar_t__ ELF_K_ELF ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  archive_entry_gid (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mode (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mtime (struct archive_entry*) ; 
 char* archive_entry_pathname (struct archive_entry*) ; 
 size_t archive_entry_size (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_uid (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_error_string (struct archive*) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 scalar_t__ archive_read_data (struct archive*,char*,size_t) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int /*<<< orphan*/  archive_read_open_fd (struct archive*,int,int) ; 
 int /*<<< orphan*/  archive_read_support_format_ar (struct archive*) ; 
 int /*<<< orphan*/  elf_errmsg (int) ; 
 scalar_t__ elf_kind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * elf_memory (char*,size_t) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  process_ar_obj (struct elfcopy*,struct ar_obj*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ac_read_objs(struct elfcopy *ecp, int ifd)
{
	struct archive		*a;
	struct archive_entry	*entry;
	struct ar_obj		*obj;
	const char		*name;
	char			*buff;
	size_t			 size;
	int			 r;

	ecp->rela_off = 0;
	if (lseek(ifd, 0, SEEK_SET) == -1)
		err(EXIT_FAILURE, "lseek failed");
	if ((a = archive_read_new()) == NULL)
		errx(EXIT_FAILURE, "archive_read_new failed");
	archive_read_support_format_ar(a);
	AC(archive_read_open_fd(a, ifd, 10240));
	for(;;) {
		r = archive_read_next_header(a, &entry);
		if (r == ARCHIVE_FATAL)
			errx(EXIT_FAILURE, "%s", archive_error_string(a));
		if (r == ARCHIVE_EOF)
			break;
		if (r == ARCHIVE_WARN || r == ARCHIVE_RETRY)
			warnx("%s", archive_error_string(a));
		if (r == ARCHIVE_RETRY)
			continue;

		name = archive_entry_pathname(entry);

		/* skip pseudo members. */
		if (strcmp(name, "/") == 0 || strcmp(name, "//") == 0)
			continue;

		size = archive_entry_size(entry);

		if (size > 0) {
			if ((buff = malloc(size)) == NULL)
				err(EXIT_FAILURE, "malloc failed");
			if (archive_read_data(a, buff, size) != (ssize_t)size) {
				warnx("%s", archive_error_string(a));
				free(buff);
				continue;
			}
			if ((obj = malloc(sizeof(*obj))) == NULL)
				err(EXIT_FAILURE, "malloc failed");
			if ((obj->name = strdup(name)) == NULL)
				err(EXIT_FAILURE, "strdup failed");
			obj->buf = buff;
			obj->uid = archive_entry_uid(entry);
			obj->gid = archive_entry_gid(entry);
			obj->md = archive_entry_mode(entry);
			obj->mtime = archive_entry_mtime(entry);
			if ((ecp->ein = elf_memory(buff, size)) == NULL)
				errx(EXIT_FAILURE, "elf_memory() failed: %s",
				    elf_errmsg(-1));
			if (elf_kind(ecp->ein) != ELF_K_ELF)
				errx(EXIT_FAILURE,
				    "file format not recognized");
			process_ar_obj(ecp, obj);
		}
	}
	AC(archive_read_close(a));
	ACV(archive_read_free(a));
}