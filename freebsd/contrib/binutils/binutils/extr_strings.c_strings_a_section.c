#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_size; } ;
struct TYPE_6__ {scalar_t__ filesize; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ filename_and_size_t ;
typedef  int /*<<< orphan*/  file_ptr ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  filepos; } ;
typedef  TYPE_2__ asection ;

/* Variables and functions */
 int DATA_FLAGS ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bfd_get_section_contents (int /*<<< orphan*/ *,TYPE_2__*,void*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ bfd_get_section_size (TYPE_2__*) ; 
 scalar_t__ bfd_stat (int /*<<< orphan*/ *,struct stat*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  got_a_section ; 
 int /*<<< orphan*/  print_strings (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,void*) ; 
 void* xmalloc (scalar_t__) ; 

__attribute__((used)) static void
strings_a_section (bfd *abfd, asection *sect, void *arg)
{
  filename_and_size_t * filename_and_sizep;
  bfd_size_type *filesizep;
  bfd_size_type sectsize;
  void *mem;
     
  if ((sect->flags & DATA_FLAGS) != DATA_FLAGS)
    return;

  sectsize = bfd_get_section_size (sect);
     
  if (sectsize <= 0)
    return;

  /* Get the size of the file.  This might have been cached for us.  */
  filename_and_sizep = (filename_and_size_t *) arg;
  filesizep = & filename_and_sizep->filesize;

  if (*filesizep == 0)
    {
      struct stat st;
      
      if (bfd_stat (abfd, &st))
	return;

      /* Cache the result so that we do not repeatedly stat this file.  */
      *filesizep = st.st_size;
    }

  /* Compare the size of the section against the size of the file.
     If the section is bigger then the file must be corrupt and
     we should not try dumping it.  */
  if (sectsize >= *filesizep)
    return;

  mem = xmalloc (sectsize);

  if (bfd_get_section_contents (abfd, sect, mem, (file_ptr) 0, sectsize))
    {
      got_a_section = TRUE;

      print_strings (filename_and_sizep->filename, NULL, sect->filepos,
		     0, sectsize, mem);
    }

  free (mem);
}