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
struct stat {long st_size; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  file_ptr ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int BUFSIZE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 char* _ (char*) ; 
 scalar_t__ bfd_bread (char*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_bwrite (char*,scalar_t__,int /*<<< orphan*/ *) ; 
 char* bfd_get_archive_filename (int /*<<< orphan*/ *) ; 
 char* bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_nonfatal (char*) ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_stat_arch_elt (int /*<<< orphan*/ *,struct stat*) ; 
 int /*<<< orphan*/  chmod (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  non_fatal (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 scalar_t__ verbose ; 
 char* xmalloc (int) ; 

__attribute__((used)) static bfd_boolean
copy_unknown_object (bfd *ibfd, bfd *obfd)
{
  char *cbuf;
  int tocopy;
  long ncopied;
  long size;
  struct stat buf;

  if (bfd_stat_arch_elt (ibfd, &buf) != 0)
    {
      bfd_nonfatal (bfd_get_archive_filename (ibfd));
      return FALSE;
    }

  size = buf.st_size;
  if (size < 0)
    {
      non_fatal (_("stat returns negative size for `%s'"),
		 bfd_get_archive_filename (ibfd));
      return FALSE;
    }

  if (bfd_seek (ibfd, (file_ptr) 0, SEEK_SET) != 0)
    {
      bfd_nonfatal (bfd_get_archive_filename (ibfd));
      return FALSE;
    }

  if (verbose)
    printf (_("copy from `%s' [unknown] to `%s' [unknown]\n"),
	    bfd_get_archive_filename (ibfd), bfd_get_filename (obfd));

  cbuf = xmalloc (BUFSIZE);
  ncopied = 0;
  while (ncopied < size)
    {
      tocopy = size - ncopied;
      if (tocopy > BUFSIZE)
	tocopy = BUFSIZE;

      if (bfd_bread (cbuf, (bfd_size_type) tocopy, ibfd)
	  != (bfd_size_type) tocopy)
	{
	  bfd_nonfatal (bfd_get_archive_filename (ibfd));
	  free (cbuf);
	  return FALSE;
	}

      if (bfd_bwrite (cbuf, (bfd_size_type) tocopy, obfd)
	  != (bfd_size_type) tocopy)
	{
	  bfd_nonfatal (bfd_get_filename (obfd));
	  free (cbuf);
	  return FALSE;
	}

      ncopied += tocopy;
    }

  chmod (bfd_get_filename (obfd), buf.st_mode);
  free (cbuf);
  return TRUE;
}