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
struct line_info_table {struct line_info* lcl_head; struct line_info* last_line; int /*<<< orphan*/  abfd; } ;
struct line_info {unsigned int line; unsigned int column; int end_sequence; struct line_info* prev_line; int /*<<< orphan*/ * filename; int /*<<< orphan*/  address; } ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int bfd_size_type ;

/* Variables and functions */
 void* bfd_alloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ new_line_sorts_after (struct line_info*,struct line_info*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
add_line_info (struct line_info_table *table,
	       bfd_vma address,
	       char *filename,
	       unsigned int line,
	       unsigned int column,
	       int end_sequence)
{
  bfd_size_type amt = sizeof (struct line_info);
  struct line_info* info = bfd_alloc (table->abfd, amt);

  /* Set member data of 'info'.  */
  info->address = address;
  info->line = line;
  info->column = column;
  info->end_sequence = end_sequence;

  if (filename && filename[0])
    {
      info->filename = bfd_alloc (table->abfd, strlen (filename) + 1);
      if (info->filename)
	strcpy (info->filename, filename);
    }
  else
    info->filename = NULL;

  /* Find the correct location for 'info'.  Normally we will receive
     new line_info data 1) in order and 2) with increasing VMAs.
     However some compilers break the rules (cf. decode_line_info) and
     so we include some heuristics for quickly finding the correct
     location for 'info'. In particular, these heuristics optimize for
     the common case in which the VMA sequence that we receive is a
     list of locally sorted VMAs such as
       p...z a...j  (where a < j < p < z)

     Note: table->lcl_head is used to head an *actual* or *possible*
     sequence within the list (such as a...j) that is not directly
     headed by table->last_line

     Note: we may receive duplicate entries from 'decode_line_info'.  */

  if (!table->last_line
      || new_line_sorts_after (info, table->last_line))
    {
      /* Normal case: add 'info' to the beginning of the list */
      info->prev_line = table->last_line;
      table->last_line = info;

      /* lcl_head: initialize to head a *possible* sequence at the end.  */
      if (!table->lcl_head)
	table->lcl_head = info;
    }
  else if (!new_line_sorts_after (info, table->lcl_head)
	   && (!table->lcl_head->prev_line
	       || new_line_sorts_after (info, table->lcl_head->prev_line)))
    {
      /* Abnormal but easy: lcl_head is the head of 'info'.  */
      info->prev_line = table->lcl_head->prev_line;
      table->lcl_head->prev_line = info;
    }
  else
    {
      /* Abnormal and hard: Neither 'last_line' nor 'lcl_head' are valid
	 heads for 'info'.  Reset 'lcl_head'.  */
      struct line_info* li2 = table->last_line; /* always non-NULL */
      struct line_info* li1 = li2->prev_line;

      while (li1)
	{
	  if (!new_line_sorts_after (info, li2)
	      && new_line_sorts_after (info, li1))
	    break;

	  li2 = li1; /* always non-NULL */
	  li1 = li1->prev_line;
	}
      table->lcl_head = li2;
      info->prev_line = table->lcl_head->prev_line;
      table->lcl_head->prev_line = info;
    }
}