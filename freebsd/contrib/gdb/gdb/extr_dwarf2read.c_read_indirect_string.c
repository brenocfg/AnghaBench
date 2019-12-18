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
struct comp_unit_head {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;
typedef  size_t LONGEST ;

/* Variables and functions */
 int HOST_CHAR_BIT ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 char* dwarf_str_buffer ; 
 size_t dwarf_str_size ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 size_t read_offset (int /*<<< orphan*/ *,char*,struct comp_unit_head const*,int*) ; 

__attribute__((used)) static char *
read_indirect_string (bfd *abfd, char *buf,
		      const struct comp_unit_head *cu_header,
		      unsigned int *bytes_read_ptr)
{
  LONGEST str_offset = read_offset (abfd, buf, cu_header,
				    (int *) bytes_read_ptr);

  if (dwarf_str_buffer == NULL)
    {
      error ("DW_FORM_strp used without .debug_str section [in module %s]",
		      bfd_get_filename (abfd));
      return NULL;
    }
  if (str_offset >= dwarf_str_size)
    {
      error ("DW_FORM_strp pointing outside of .debug_str section [in module %s]",
		      bfd_get_filename (abfd));
      return NULL;
    }
  gdb_assert (HOST_CHAR_BIT == 8);
  if (dwarf_str_buffer[str_offset] == '\0')
    return NULL;
  return dwarf_str_buffer + str_offset;
}