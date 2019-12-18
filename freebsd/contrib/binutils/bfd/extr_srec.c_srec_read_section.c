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
typedef  int bfd_vma ;
typedef  int bfd_size_type ;
typedef  int bfd_byte ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_3__ {int size; int vma; int /*<<< orphan*/  filepos; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int EOF ; 
 scalar_t__ FALSE ; 
 int HEX (int*) ; 
 scalar_t__ ISHEX (int) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ TRUE ; 
 unsigned int bfd_bread (int*,int,int /*<<< orphan*/ *) ; 
 int* bfd_malloc (int) ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int*) ; 
 int srec_get_byte (int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static bfd_boolean
srec_read_section (bfd *abfd, asection *section, bfd_byte *contents)
{
  int c;
  bfd_size_type sofar = 0;
  bfd_boolean error = FALSE;
  bfd_byte *buf = NULL;
  size_t bufsize = 0;

  if (bfd_seek (abfd, section->filepos, SEEK_SET) != 0)
    goto error_return;

  while ((c = srec_get_byte (abfd, &error)) != EOF)
    {
      bfd_byte hdr[3];
      unsigned int bytes;
      bfd_vma address;
      bfd_byte *data;

      if (c == '\r' || c == '\n')
	continue;

      /* This is called after srec_scan has already been called, so we
	 ought to know the exact format.  */
      BFD_ASSERT (c == 'S');

      if (bfd_bread (hdr, (bfd_size_type) 3, abfd) != 3)
	goto error_return;

      BFD_ASSERT (ISHEX (hdr[1]) && ISHEX (hdr[2]));

      bytes = HEX (hdr + 1);

      if (bytes * 2 > bufsize)
	{
	  if (buf != NULL)
	    free (buf);
	  buf = bfd_malloc ((bfd_size_type) bytes * 2);
	  if (buf == NULL)
	    goto error_return;
	  bufsize = bytes * 2;
	}

      if (bfd_bread (buf, (bfd_size_type) bytes * 2, abfd) != bytes * 2)
	goto error_return;

      address = 0;
      data = buf;
      switch (hdr[0])
	{
	default:
	  BFD_ASSERT (sofar == section->size);
	  if (buf != NULL)
	    free (buf);
	  return TRUE;

	case '3':
	  address = HEX (data);
	  data += 2;
	  --bytes;
	  /* Fall through.  */
	case '2':
	  address = (address << 8) | HEX (data);
	  data += 2;
	  --bytes;
	  /* Fall through.  */
	case '1':
	  address = (address << 8) | HEX (data);
	  data += 2;
	  address = (address << 8) | HEX (data);
	  data += 2;
	  bytes -= 2;

	  if (address != section->vma + sofar)
	    {
	      /* We've come to the end of this section.  */
	      BFD_ASSERT (sofar == section->size);
	      if (buf != NULL)
		free (buf);
	      return TRUE;
	    }

	  /* Don't consider checksum.  */
	  --bytes;

	  while (bytes-- != 0)
	    {
	      contents[sofar] = HEX (data);
	      data += 2;
	      ++sofar;
	    }

	  break;
	}
    }

  if (error)
    goto error_return;

  BFD_ASSERT (sofar == section->size);

  if (buf != NULL)
    free (buf);

  return TRUE;

 error_return:
  if (buf != NULL)
    free (buf);
  return FALSE;
}