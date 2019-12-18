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
struct ieee_range {int low; int high; struct ieee_range* next; } ;
struct ieee_handle {int highaddr; char* modname; TYPE_2__* abfd; struct ieee_range* ranges; int /*<<< orphan*/  data; int /*<<< orphan*/  linenos; int /*<<< orphan*/  vars; int /*<<< orphan*/  types; int /*<<< orphan*/  lineno_filename; int /*<<< orphan*/  filename; int /*<<< orphan*/ * pending_lineno_filename; int /*<<< orphan*/  cxx; } ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_6__ {int flags; int index; struct TYPE_6__* next; } ;
typedef  TYPE_1__ asection ;
struct TYPE_7__ {TYPE_1__* sections; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int IEEE_SECTION_NUMBER_BASE ; 
 int SEC_CODE ; 
 int SEC_READONLY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bfd_get_section_vma (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ bfd_section_size (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ieee_add_range (struct ieee_handle*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ieee_append_buffer (struct ieee_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ieee_bb_record_enum ; 
 scalar_t__ ieee_be_record_enum ; 
 int /*<<< orphan*/  ieee_buffer_emptyp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee_change_buffer (struct ieee_handle*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee_lineno (void*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee_write_byte (struct ieee_handle*,int) ; 
 int /*<<< orphan*/  ieee_write_id (struct ieee_handle*,char*) ; 
 int /*<<< orphan*/  ieee_write_number (struct ieee_handle*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
ieee_finish_compilation_unit (struct ieee_handle *info)
{
  struct ieee_range *r;

  if (! ieee_buffer_emptyp (&info->types))
    {
      if (! ieee_change_buffer (info, &info->types)
	  || ! ieee_write_byte (info, (int) ieee_be_record_enum))
	return FALSE;
    }

  if (! ieee_buffer_emptyp (&info->cxx))
    {
      /* Append any C++ information to the global function and
         variable information.  */
      assert (! ieee_buffer_emptyp (&info->vars));
      if (! ieee_change_buffer (info, &info->vars))
	return FALSE;

      /* We put the pmisc records in a dummy procedure, just as the
         MRI compiler does.  */
      if (! ieee_write_byte (info, (int) ieee_bb_record_enum)
	  || ! ieee_write_byte (info, 6)
	  || ! ieee_write_number (info, 0)
	  || ! ieee_write_id (info, "__XRYCPP")
	  || ! ieee_write_number (info, 0)
	  || ! ieee_write_number (info, 0)
	  || ! ieee_write_number (info, info->highaddr - 1)
	  || ! ieee_append_buffer (info, &info->vars, &info->cxx)
	  || ! ieee_change_buffer (info, &info->vars)
	  || ! ieee_write_byte (info, (int) ieee_be_record_enum)
	  || ! ieee_write_number (info, info->highaddr - 1))
	return FALSE;
    }

  if (! ieee_buffer_emptyp (&info->vars))
    {
      if (! ieee_change_buffer (info, &info->vars)
	  || ! ieee_write_byte (info, (int) ieee_be_record_enum))
	return FALSE;
    }

  if (info->pending_lineno_filename != NULL)
    {
      /* Force out the pending line number.  */
      if (! ieee_lineno ((void *) info, (const char *) NULL, 0, (bfd_vma) -1))
	return FALSE;
    }
  if (! ieee_buffer_emptyp (&info->linenos))
    {
      if (! ieee_change_buffer (info, &info->linenos)
	  || ! ieee_write_byte (info, (int) ieee_be_record_enum))
	return FALSE;
      if (strcmp (info->filename, info->lineno_filename) != 0)
	{
	  /* We were not in the main file.  We just closed the
             included line number block, and now we must close the
             main line number block.  */
	  if (! ieee_write_byte (info, (int) ieee_be_record_enum))
	    return FALSE;
	}
    }

  if (! ieee_append_buffer (info, &info->data, &info->types)
      || ! ieee_append_buffer (info, &info->data, &info->vars)
      || ! ieee_append_buffer (info, &info->data, &info->linenos))
    return FALSE;

  /* Build BB10/BB11 blocks based on the ranges we recorded.  */
  if (! ieee_change_buffer (info, &info->data))
    return FALSE;

  if (! ieee_write_byte (info, (int) ieee_bb_record_enum)
      || ! ieee_write_byte (info, 10)
      || ! ieee_write_number (info, 0)
      || ! ieee_write_id (info, info->modname)
      || ! ieee_write_id (info, "")
      || ! ieee_write_number (info, 0)
      || ! ieee_write_id (info, "GNU objcopy"))
    return FALSE;

  for (r = info->ranges; r != NULL; r = r->next)
    {
      bfd_vma low, high;
      asection *s;
      int kind;

      low = r->low;
      high = r->high;

      /* Find the section corresponding to this range.  */
      for (s = info->abfd->sections; s != NULL; s = s->next)
	{
	  if (bfd_get_section_vma (info->abfd, s) <= low
	      && high <= (bfd_get_section_vma (info->abfd, s)
			  + bfd_section_size (info->abfd, s)))
	    break;
	}

      if (s == NULL)
	{
	  /* Just ignore this range.  */
	  continue;
	}

      /* Coalesce ranges if it seems reasonable.  */
      while (r->next != NULL
	     && high + 0x1000 >= r->next->low
	     && (r->next->high
		 <= (bfd_get_section_vma (info->abfd, s)
		     + bfd_section_size (info->abfd, s))))
	{
	  r = r->next;
	  high = r->high;
	}

      if ((s->flags & SEC_CODE) != 0)
	kind = 1;
      else if ((s->flags & SEC_READONLY) != 0)
	kind = 3;
      else
	kind = 2;

      if (! ieee_write_byte (info, (int) ieee_bb_record_enum)
	  || ! ieee_write_byte (info, 11)
	  || ! ieee_write_number (info, 0)
	  || ! ieee_write_id (info, "")
	  || ! ieee_write_number (info, kind)
	  || ! ieee_write_number (info, s->index + IEEE_SECTION_NUMBER_BASE)
	  || ! ieee_write_number (info, low)
	  || ! ieee_write_byte (info, (int) ieee_be_record_enum)
	  || ! ieee_write_number (info, high - low))
	return FALSE;

      /* Add this range to the list of global ranges.  */
      if (! ieee_add_range (info, TRUE, low, high))
	return FALSE;
    }

  if (! ieee_write_byte (info, (int) ieee_be_record_enum))
    return FALSE;

  return TRUE;
}