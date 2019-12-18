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
typedef  int /*<<< orphan*/  file_ptr ;
typedef  int bfd_size_type ;
typedef  char bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_3__ {char* contents; int sh_size; int /*<<< orphan*/  sh_offset; } ;
typedef  TYPE_1__ Elf_Internal_Shdr ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 char* bfd_alloc (int /*<<< orphan*/ *,int) ; 
 int bfd_bread (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_error_file_truncated ; 
 scalar_t__ bfd_error_system_call ; 
 scalar_t__ bfd_get_error () ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 TYPE_1__** elf_elfsections (int /*<<< orphan*/ *) ; 
 unsigned int elf_numsections (int /*<<< orphan*/ *) ; 

char *
bfd_elf_get_str_section (bfd *abfd, unsigned int shindex)
{
  Elf_Internal_Shdr **i_shdrp;
  bfd_byte *shstrtab = NULL;
  file_ptr offset;
  bfd_size_type shstrtabsize;

  i_shdrp = elf_elfsections (abfd);
  if (i_shdrp == 0
      || shindex >= elf_numsections (abfd)
      || i_shdrp[shindex] == 0)
    return NULL;

  shstrtab = i_shdrp[shindex]->contents;
  if (shstrtab == NULL)
    {
      /* No cached one, attempt to read, and cache what we read.  */
      offset = i_shdrp[shindex]->sh_offset;
      shstrtabsize = i_shdrp[shindex]->sh_size;

      /* Allocate and clear an extra byte at the end, to prevent crashes
	 in case the string table is not terminated.  */
      if (shstrtabsize + 1 == 0
	  || (shstrtab = bfd_alloc (abfd, shstrtabsize + 1)) == NULL
	  || bfd_seek (abfd, offset, SEEK_SET) != 0)
	shstrtab = NULL;
      else if (bfd_bread (shstrtab, shstrtabsize, abfd) != shstrtabsize)
	{
	  if (bfd_get_error () != bfd_error_system_call)
	    bfd_set_error (bfd_error_file_truncated);
	  shstrtab = NULL;
	}
      else
	shstrtab[shstrtabsize] = '\0';
      i_shdrp[shindex]->contents = shstrtab;
    }
  return (char *) shstrtab;
}