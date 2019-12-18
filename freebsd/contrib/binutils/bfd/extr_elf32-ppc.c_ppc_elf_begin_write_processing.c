#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct bfd_link_info {TYPE_1__* input_bfds; } ;
typedef  unsigned long bfd_size_type ;
struct TYPE_13__ {struct TYPE_13__* link_next; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_14__ {unsigned long size; int /*<<< orphan*/  filepos; } ;
typedef  TYPE_2__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  APUINFO_LABEL ; 
 int /*<<< orphan*/  APUINFO_SECTION_NAME ; 
 int /*<<< orphan*/  SEEK_SET ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (char const*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apuinfo_list_add (unsigned long) ; 
 int /*<<< orphan*/  apuinfo_list_init () ; 
 unsigned int apuinfo_list_length () ; 
 unsigned long bfd_bread (char*,unsigned long,TYPE_1__*) ; 
 unsigned long bfd_get_32 (TYPE_1__*,char*) ; 
 TYPE_2__* bfd_get_section_by_name (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* bfd_malloc (unsigned long) ; 
 scalar_t__ bfd_seek (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_section_size (TYPE_1__*,TYPE_2__*,unsigned long) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (char const*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ppc_elf_begin_write_processing (bfd *abfd, struct bfd_link_info *link_info)
{
  bfd *ibfd;
  asection *asec;
  char *buffer;
  unsigned num_input_sections;
  bfd_size_type	output_section_size;
  unsigned i;
  unsigned num_entries;
  unsigned long	offset;
  unsigned long length;
  const char *error_message = NULL;

  if (link_info == NULL)
    return;

  /* Scan the input bfds, looking for apuinfo sections.  */
  num_input_sections = 0;
  output_section_size = 0;

  for (ibfd = link_info->input_bfds; ibfd; ibfd = ibfd->link_next)
    {
      asec = bfd_get_section_by_name (ibfd, APUINFO_SECTION_NAME);
      if (asec)
	{
	  ++ num_input_sections;
	  output_section_size += asec->size;
	}
    }

  /* We need at least one input sections
     in order to make merging worthwhile.  */
  if (num_input_sections < 1)
    return;

  /* Just make sure that the output section exists as well.  */
  asec = bfd_get_section_by_name (abfd, APUINFO_SECTION_NAME);
  if (asec == NULL)
    return;

  /* Allocate a buffer for the contents of the input sections.  */
  buffer = bfd_malloc (output_section_size);
  if (buffer == NULL)
    return;

  offset = 0;
  apuinfo_list_init ();

  /* Read in the input sections contents.  */
  for (ibfd = link_info->input_bfds; ibfd; ibfd = ibfd->link_next)
    {
      unsigned long datum;
      char *ptr;

      asec = bfd_get_section_by_name (ibfd, APUINFO_SECTION_NAME);
      if (asec == NULL)
	continue;

      length = asec->size;
      if (length < 24)
	{
	  error_message = _("corrupt or empty %s section in %B");
	  goto fail;
	}

      if (bfd_seek (ibfd, asec->filepos, SEEK_SET) != 0
	  || (bfd_bread (buffer + offset, length, ibfd) != length))
	{
	  error_message = _("unable to read in %s section from %B");
	  goto fail;
	}

      /* Process the contents of the section.  */
      ptr = buffer + offset;
      error_message = _("corrupt %s section in %B");

      /* Verify the contents of the header.  Note - we have to
	 extract the values this way in order to allow for a
	 host whose endian-ness is different from the target.  */
      datum = bfd_get_32 (ibfd, ptr);
      if (datum != sizeof APUINFO_LABEL)
	goto fail;

      datum = bfd_get_32 (ibfd, ptr + 8);
      if (datum != 0x2)
	goto fail;

      if (strcmp (ptr + 12, APUINFO_LABEL) != 0)
	goto fail;

      /* Get the number of bytes used for apuinfo entries.  */
      datum = bfd_get_32 (ibfd, ptr + 4);
      if (datum + 20 != length)
	goto fail;

      /* Make sure that we do not run off the end of the section.  */
      if (offset + length > output_section_size)
	goto fail;

      /* Scan the apuinfo section, building a list of apuinfo numbers.  */
      for (i = 0; i < datum; i += 4)
	apuinfo_list_add (bfd_get_32 (ibfd, ptr + 20 + i));

      /* Update the offset.  */
      offset += length;
    }

  error_message = NULL;

  /* Compute the size of the output section.  */
  num_entries = apuinfo_list_length ();
  output_section_size = 20 + num_entries * 4;

  asec = bfd_get_section_by_name (abfd, APUINFO_SECTION_NAME);

  if (! bfd_set_section_size (abfd, asec, output_section_size))
    ibfd = abfd,
      error_message = _("warning: unable to set size of %s section in %B");

 fail:
  free (buffer);

  if (error_message)
    (*_bfd_error_handler) (error_message, ibfd, APUINFO_SECTION_NAME);
}