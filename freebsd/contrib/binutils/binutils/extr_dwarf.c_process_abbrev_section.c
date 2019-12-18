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

/* Variables and functions */
 int /*<<< orphan*/  add_abbrev (unsigned long,unsigned long,int) ; 
 int /*<<< orphan*/  add_abbrev_attr (unsigned long,unsigned long) ; 
 int /*<<< orphan*/ * first_abbrev ; 
 unsigned long read_leb128 (unsigned char*,unsigned int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char *
process_abbrev_section (unsigned char *start, unsigned char *end)
{
  if (first_abbrev != NULL)
    return NULL;

  while (start < end)
    {
      unsigned int bytes_read;
      unsigned long entry;
      unsigned long tag;
      unsigned long attribute;
      int children;

      entry = read_leb128 (start, & bytes_read, 0);
      start += bytes_read;

      /* A single zero is supposed to end the section according
	 to the standard.  If there's more, then signal that to
	 the caller.  */
      if (entry == 0)
	return start == end ? NULL : start;

      tag = read_leb128 (start, & bytes_read, 0);
      start += bytes_read;

      children = *start++;

      add_abbrev (entry, tag, children);

      do
	{
	  unsigned long form;

	  attribute = read_leb128 (start, & bytes_read, 0);
	  start += bytes_read;

	  form = read_leb128 (start, & bytes_read, 0);
	  start += bytes_read;

	  if (attribute != 0)
	    add_abbrev_attr (attribute, form);
	}
      while (attribute != 0);
    }

  return NULL;
}