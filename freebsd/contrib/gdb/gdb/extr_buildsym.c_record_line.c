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
struct subfile {int line_vector_length; struct linetable* line_vector; } ;
struct linetable_entry {int line; int /*<<< orphan*/  pc; } ;
struct linetable {int nitems; struct linetable_entry* item; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_BITS_REMOVE (int /*<<< orphan*/ ) ; 
 int INITIAL_LINE_VECTOR_LENGTH ; 
 int have_line_numbers ; 
 scalar_t__ xmalloc (int) ; 
 scalar_t__ xrealloc (char*,int) ; 

void
record_line (struct subfile *subfile, int line, CORE_ADDR pc)
{
  struct linetable_entry *e;
  /* Ignore the dummy line number in libg.o */

  if (line == 0xffff)
    {
      return;
    }

  /* Make sure line vector exists and is big enough.  */
  if (!subfile->line_vector)
    {
      subfile->line_vector_length = INITIAL_LINE_VECTOR_LENGTH;
      subfile->line_vector = (struct linetable *)
	xmalloc (sizeof (struct linetable)
	   + subfile->line_vector_length * sizeof (struct linetable_entry));
      subfile->line_vector->nitems = 0;
      have_line_numbers = 1;
    }

  if (subfile->line_vector->nitems + 1 >= subfile->line_vector_length)
    {
      subfile->line_vector_length *= 2;
      subfile->line_vector = (struct linetable *)
	xrealloc ((char *) subfile->line_vector,
		  (sizeof (struct linetable)
		   + (subfile->line_vector_length
		      * sizeof (struct linetable_entry))));
    }

  e = subfile->line_vector->item + subfile->line_vector->nitems++;
  e->line = line;
  e->pc = ADDR_BITS_REMOVE(pc);
}