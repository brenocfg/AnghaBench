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
struct stat {size_t st_size; scalar_t__ st_gid; scalar_t__ st_uid; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int O_CREAT ; 
 int O_EXCL ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_WRONLY ; 
 char* alloca (size_t) ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 scalar_t__ chown (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  fatal (char*,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fstat (int,struct stat*) ; 
 char* g_etcbegin ; 
 char* g_etcend ; 
 char* g_etcfile ; 
 int getpid () ; 
 char* malloc (size_t) ; 
 int open (char*,int,...) ; 
 size_t read (int,char*,size_t) ; 
 int rename (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,int) ; 
 int strlen (char*) ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void
etcsystem_prune(void)
{
	struct stat sbuf;
	size_t sz;
	char *buf, *start, *end;
	int fd;
	char *fname = g_etcfile, *tmpname;

	if ((fd = open(fname, O_RDONLY)) == -1)
		fatal("failed to open %s", fname);

	if (fstat(fd, &sbuf) == -1)
		fatal("failed to fstat %s", fname);

	if ((buf = malloc((sz = sbuf.st_size) + 1)) == NULL)
		fatal("failed to allocate memory for %s", fname);

	if (read(fd, buf, sz) != sz)
		fatal("failed to read %s", fname);

	buf[sz] = '\0';
	(void) close(fd);

	if ((start = strstr(buf, g_etcbegin)) == NULL)
		goto out;

	if (strlen(buf) != sz) {
		fatal("embedded nul byte in %s; manual repair of %s "
		    "required\n", fname, fname);
	}

	if (strstr(start + 1, g_etcbegin) != NULL) {
		fatal("multiple start sentinels in %s; manual repair of %s "
		    "required\n", fname, fname);
	}

	if ((end = strstr(buf, g_etcend)) == NULL) {
		fatal("missing end sentinel in %s; manual repair of %s "
		    "required\n", fname, fname);
	}

	if (start > end) {
		fatal("end sentinel preceeds start sentinel in %s; manual "
		    "repair of %s required\n", fname, fname);
	}

	end += strlen(g_etcend) + 1;
	bcopy(end, start, strlen(end) + 1);

	tmpname = alloca(sz = strlen(fname) + 80);
	(void) snprintf(tmpname, sz, "%s.dtrace.%d", fname, getpid());

	if ((fd = open(tmpname,
	    O_WRONLY | O_CREAT | O_EXCL, sbuf.st_mode)) == -1)
		fatal("failed to create %s", tmpname);

	if (write(fd, buf, strlen(buf)) < strlen(buf)) {
		(void) unlink(tmpname);
		fatal("failed to write to %s", tmpname);
	}

	(void) close(fd);

	if (chown(tmpname, sbuf.st_uid, sbuf.st_gid) != 0) {
		(void) unlink(tmpname);
		fatal("failed to chown(2) %s to uid %d, gid %d", tmpname,
		    (int)sbuf.st_uid, (int)sbuf.st_gid);
	}

	if (rename(tmpname, fname) == -1)
		fatal("rename of %s to %s failed", tmpname, fname);

	error("cleaned up forceload directives in %s\n", fname);
out:
	free(buf);
}