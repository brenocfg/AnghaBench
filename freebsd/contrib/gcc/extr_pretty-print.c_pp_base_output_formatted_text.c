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
struct chunk_info {char** args; struct chunk_info* prev; } ;
typedef  int /*<<< orphan*/  pretty_printer ;
struct TYPE_3__ {scalar_t__ line_length; int /*<<< orphan*/  chunk_obstack; struct chunk_info* cur_chunk_array; int /*<<< orphan*/  formatted_obstack; int /*<<< orphan*/ * obstack; } ;
typedef  TYPE_1__ output_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,struct chunk_info*) ; 
 TYPE_1__* pp_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_string (int /*<<< orphan*/ *,char const*) ; 

void
pp_base_output_formatted_text (pretty_printer *pp)
{
  unsigned int chunk;
  output_buffer *buffer = pp_buffer (pp);
  struct chunk_info *chunk_array = buffer->cur_chunk_array;
  const char **args = chunk_array->args;

  gcc_assert (buffer->obstack == &buffer->formatted_obstack);
  gcc_assert (buffer->line_length == 0);

  /* This is a third phase, first 2 phases done in pp_base_format_args.
     Now we actually print it.  */
  for (chunk = 0; args[chunk]; chunk++)
    pp_string (pp, args[chunk]);

  /* Deallocate the chunk structure and everything after it (i.e. the
     associated series of formatted strings).  */
  buffer->cur_chunk_array = chunk_array->prev;
  obstack_free (&buffer->chunk_obstack, chunk_array);
}