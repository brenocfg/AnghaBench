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
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int bfd_bread (char*,int,int /*<<< orphan*/ *) ; 
 long bfd_h_get_32 (int /*<<< orphan*/ ,unsigned char*) ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_stringtab () ; 
 int /*<<< orphan*/  memcpy (char*,unsigned char*,int) ; 
 char* stringtab ; 
 int /*<<< orphan*/  symfile_bfd ; 
 scalar_t__ xmalloc (long) ; 

__attribute__((used)) static int
init_stringtab (bfd *abfd, long offset)
{
  long length;
  int val;
  unsigned char lengthbuf[4];

  free_stringtab ();

  /* If the file is stripped, the offset might be zero, indicating no
     string table.  Just return with `stringtab' set to null. */
  if (offset == 0)
    return 0;

  if (bfd_seek (abfd, offset, 0) < 0)
    return -1;

  val = bfd_bread ((char *) lengthbuf, sizeof lengthbuf, abfd);
  length = bfd_h_get_32 (symfile_bfd, lengthbuf);

  /* If no string table is needed, then the file may end immediately
     after the symbols.  Just return with `stringtab' set to null. */
  if (val != sizeof lengthbuf || length < sizeof lengthbuf)
    return 0;

  stringtab = (char *) xmalloc (length);
  /* This is in target format (probably not very useful, and not currently
     used), not host format.  */
  memcpy (stringtab, lengthbuf, sizeof lengthbuf);
  if (length == sizeof length)	/* Empty table -- just the count */
    return 0;

  val = bfd_bread (stringtab + sizeof lengthbuf, length - sizeof lengthbuf,
		   abfd);
  if (val != length - sizeof lengthbuf || stringtab[length - 1] != '\0')
    return -1;

  return 0;
}