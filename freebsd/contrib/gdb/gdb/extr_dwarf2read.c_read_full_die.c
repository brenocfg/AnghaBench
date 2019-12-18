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
struct dwarf2_cu {int dummy; } ;
struct die_info {unsigned int abbrev; unsigned int offset; int num_attrs; struct attribute* attrs; int /*<<< orphan*/ * type; scalar_t__ tag; } ;
struct attribute {int dummy; } ;
struct abbrev_info {int num_attrs; int has_children; int /*<<< orphan*/ * attrs; scalar_t__ tag; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 char* bfd_get_filename (int /*<<< orphan*/ *) ; 
 struct abbrev_info* dwarf2_lookup_abbrev (unsigned int,struct dwarf2_cu*) ; 
 struct die_info* dwarf_alloc_die () ; 
 char* dwarf_info_buffer ; 
 int /*<<< orphan*/  error (char*,unsigned int,char*) ; 
 char* read_attribute (struct attribute*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,struct dwarf2_cu*) ; 
 unsigned int read_unsigned_leb128 (int /*<<< orphan*/ *,char*,unsigned int*) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static char *
read_full_die (struct die_info **diep, bfd *abfd, char *info_ptr,
	       struct dwarf2_cu *cu, int *has_children)
{
  unsigned int abbrev_number, bytes_read, i, offset;
  struct abbrev_info *abbrev;
  struct die_info *die;

  offset = info_ptr - dwarf_info_buffer;
  abbrev_number = read_unsigned_leb128 (abfd, info_ptr, &bytes_read);
  info_ptr += bytes_read;
  if (!abbrev_number)
    {
      die = dwarf_alloc_die ();
      die->tag = 0;
      die->abbrev = abbrev_number;
      die->type = NULL;
      *diep = die;
      *has_children = 0;
      return info_ptr;
    }

  abbrev = dwarf2_lookup_abbrev (abbrev_number, cu);
  if (!abbrev)
    {
      error ("Dwarf Error: could not find abbrev number %d [in module %s]",
	     abbrev_number, 
	     bfd_get_filename (abfd));
    }
  die = dwarf_alloc_die ();
  die->offset = offset;
  die->tag = abbrev->tag;
  die->abbrev = abbrev_number;
  die->type = NULL;

  die->num_attrs = abbrev->num_attrs;
  die->attrs = (struct attribute *)
    xmalloc (die->num_attrs * sizeof (struct attribute));

  for (i = 0; i < abbrev->num_attrs; ++i)
    {
      info_ptr = read_attribute (&die->attrs[i], &abbrev->attrs[i],
				 abfd, info_ptr, cu);
    }

  *diep = die;
  *has_children = abbrev->has_children;
  return info_ptr;
}