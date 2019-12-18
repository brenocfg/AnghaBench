#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int bfd_size_type ;
typedef  char bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_3__ {int size; int /*<<< orphan*/  filepos; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int EOF ; 
 int /*<<< orphan*/  FALSE ; 
 void* HEX2 (char*) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bfd_bread (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_error_bad_value ; 
 char* bfd_realloc (char*,int) ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int ihex_get_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
ihex_read_section (bfd *abfd, asection *section, bfd_byte *contents)
{
  int c;
  bfd_byte *p;
  bfd_byte *buf = NULL;
  size_t bufsize;
  bfd_boolean error;

  if (bfd_seek (abfd, section->filepos, SEEK_SET) != 0)
    goto error_return;

  p = contents;
  bufsize = 0;
  error = FALSE;
  while ((c = ihex_get_byte (abfd, &error)) != EOF)
    {
      char hdr[8];
      unsigned int len;
      unsigned int type;
      unsigned int i;

      if (c == '\r' || c == '\n')
	continue;

      /* This is called after ihex_scan has succeeded, so we ought to
         know the exact format.  */
      BFD_ASSERT (c == ':');

      if (bfd_bread (hdr, (bfd_size_type) 8, abfd) != 8)
	goto error_return;

      len = HEX2 (hdr);
      type = HEX2 (hdr + 6);

      /* We should only see type 0 records here.  */
      if (type != 0)
	{
	  (*_bfd_error_handler)
	    (_("%B: internal error in ihex_read_section"), abfd);
	  bfd_set_error (bfd_error_bad_value);
	  goto error_return;
	}

      if (len * 2 > bufsize)
	{
	  buf = bfd_realloc (buf, (bfd_size_type) len * 2);
	  if (buf == NULL)
	    goto error_return;
	  bufsize = len * 2;
	}

      if (bfd_bread (buf, (bfd_size_type) len * 2, abfd) != len * 2)
	goto error_return;

      for (i = 0; i < len; i++)
	*p++ = HEX2 (buf + 2 * i);
      if ((bfd_size_type) (p - contents) >= section->size)
	{
	  /* We've read everything in the section.  */
	  if (buf != NULL)
	    free (buf);
	  return TRUE;
	}

      /* Skip the checksum.  */
      if (bfd_bread (buf, (bfd_size_type) 2, abfd) != 2)
	goto error_return;
    }

  if ((bfd_size_type) (p - contents) < section->size)
    {
      (*_bfd_error_handler)
	(_("%B: bad section length in ihex_read_section"), abfd);
      bfd_set_error (bfd_error_bad_value);
      goto error_return;
    }

  if (buf != NULL)
    free (buf);

  return TRUE;

 error_return:
  if (buf != NULL)
    free (buf);
  return FALSE;
}