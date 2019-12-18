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
typedef  int /*<<< orphan*/  file_ptr ;
typedef  int /*<<< orphan*/  bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 size_t BUFSIZE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 char* _ (char*) ; 
 size_t bfd_bread (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_my_archive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_stat_arch_elt (int /*<<< orphan*/ *,struct stat*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fwrite (char*,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stdout ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ verbose ; 
 char* xmalloc (size_t) ; 

__attribute__((used)) static void
print_contents (bfd *abfd)
{
  size_t ncopied = 0;
  char *cbuf = xmalloc (BUFSIZE);
  struct stat buf;
  size_t size;
  if (bfd_stat_arch_elt (abfd, &buf) != 0)
    /* xgettext:c-format */
    fatal (_("internal stat error on %s"), bfd_get_filename (abfd));

  if (verbose)
    /* xgettext:c-format */
    printf (_("\n<%s>\n\n"), bfd_get_filename (abfd));

  bfd_seek (abfd, (file_ptr) 0, SEEK_SET);

  size = buf.st_size;
  while (ncopied < size)
    {

      size_t nread;
      size_t tocopy = size - ncopied;
      if (tocopy > BUFSIZE)
	tocopy = BUFSIZE;

      nread = bfd_bread (cbuf, (bfd_size_type) tocopy, abfd);
      if (nread != tocopy)
	/* xgettext:c-format */
	fatal (_("%s is not a valid archive"),
	       bfd_get_filename (bfd_my_archive (abfd)));

      /* fwrite in mingw32 may return int instead of size_t. Cast the
	 return value to size_t to avoid comparison between signed and
	 unsigned values.  */
      if ((size_t) fwrite (cbuf, 1, nread, stdout) != nread)
	fatal ("stdout: %s", strerror (errno));
      ncopied += tocopy;
    }
  free (cbuf);
}