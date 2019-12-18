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
struct stat {size_t st_size; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_atime; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  file_ptr ;
typedef  int /*<<< orphan*/  bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t BUFSIZE ; 
 int /*<<< orphan*/  FOPEN_WB ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  _ (char*) ; 
 size_t bfd_bread (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_my_archive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_stat_arch_elt (int /*<<< orphan*/ *,struct stat*) ; 
 int /*<<< orphan*/  chmod (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal (char*,char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fwrite (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * output_file ; 
 char* output_filename ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ preserve_dates ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  set_times (char*,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  xexit (int) ; 
 char* xmalloc (size_t) ; 

void
extract_file (bfd *abfd)
{
  FILE *ostream;
  char *cbuf = xmalloc (BUFSIZE);
  size_t nread, tocopy;
  size_t ncopied = 0;
  size_t size;
  struct stat buf;

  if (bfd_stat_arch_elt (abfd, &buf) != 0)
    /* xgettext:c-format */
    fatal (_("internal stat error on %s"), bfd_get_filename (abfd));
  size = buf.st_size;

  if (verbose)
    printf ("x - %s\n", bfd_get_filename (abfd));

  bfd_seek (abfd, (file_ptr) 0, SEEK_SET);

  ostream = NULL;
  if (size == 0)
    {
      /* Seems like an abstraction violation, eh?  Well it's OK! */
      output_filename = bfd_get_filename (abfd);

      ostream = fopen (bfd_get_filename (abfd), FOPEN_WB);
      if (ostream == NULL)
	{
	  perror (bfd_get_filename (abfd));
	  xexit (1);
	}

      output_file = ostream;
    }
  else
    while (ncopied < size)
      {
	tocopy = size - ncopied;
	if (tocopy > BUFSIZE)
	  tocopy = BUFSIZE;

	nread = bfd_bread (cbuf, (bfd_size_type) tocopy, abfd);
	if (nread != tocopy)
	  /* xgettext:c-format */
	  fatal (_("%s is not a valid archive"),
		 bfd_get_filename (bfd_my_archive (abfd)));

	/* See comment above; this saves disk arm motion */
	if (ostream == NULL)
	  {
	    /* Seems like an abstraction violation, eh?  Well it's OK! */
	    output_filename = bfd_get_filename (abfd);

	    ostream = fopen (bfd_get_filename (abfd), FOPEN_WB);
	    if (ostream == NULL)
	      {
		perror (bfd_get_filename (abfd));
		xexit (1);
	      }

	    output_file = ostream;
	  }

	/* fwrite in mingw32 may return int instead of size_t. Cast
	   the return value to size_t to avoid comparison between
	   signed and unsigned values.  */
	if ((size_t) fwrite (cbuf, 1, nread, ostream) != nread)
	  fatal ("%s: %s", output_filename, strerror (errno));
	ncopied += tocopy;
      }

  if (ostream != NULL)
    fclose (ostream);

  output_file = NULL;
  output_filename = NULL;

  chmod (bfd_get_filename (abfd), buf.st_mode);

  if (preserve_dates)
    {
      /* Set access time to modification time.  Only st_mtime is
	 initialized by bfd_stat_arch_elt.  */
      buf.st_atime = buf.st_mtime;
      set_times (bfd_get_filename (abfd), &buf);
    }

  free (cbuf);
}