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
struct TYPE_3__ {scalar_t__ len; char* ptr; } ;

/* Variables and functions */
 int AFTER_SIZE ; 
 char* AFTER_STRING ; 
 int BEFORE_SIZE ; 
 int /*<<< orphan*/  LISTING_EOF () ; 
 scalar_t__ TC_EOL_IN_INSN (char*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ) ; 
 int buffer_length ; 
 char* buffer_start ; 
 int /*<<< orphan*/  cond_finish_check (int /*<<< orphan*/ ) ; 
 TYPE_1__ from_sb ; 
 scalar_t__ from_sb_is_expansion ; 
 scalar_t__ input_file_buffer_size () ; 
 char* input_file_give_next_buffer (char*) ; 
 char* input_scrub_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  macro_nest ; 
 int /*<<< orphan*/  md_macro_end () ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,unsigned int) ; 
 int /*<<< orphan*/ * next_saved_file ; 
 int partial_size ; 
 char* partial_where ; 
 char* save_source ; 
 scalar_t__ sb_index ; 
 int /*<<< orphan*/  sb_kill (TYPE_1__*) ; 
 char* xrealloc (char*,int) ; 

char *
input_scrub_next_buffer (char **bufp)
{
  register char *limit;		/*->just after last char of buffer.  */

  if (sb_index >= 0)
    {
      if (sb_index >= from_sb.len)
	{
	  sb_kill (&from_sb);
	  if (from_sb_is_expansion
	      )
	    {
	      cond_finish_check (macro_nest);
#ifdef md_macro_end
	      /* Allow the target to clean up per-macro expansion
	         data.  */
	      md_macro_end ();
#endif
	    }
	  --macro_nest;
	  partial_where = NULL;
	  if (next_saved_file != NULL)
	    *bufp = input_scrub_pop (next_saved_file);
	  return partial_where;
	}

      partial_where = from_sb.ptr + from_sb.len;
      partial_size = 0;
      *bufp = from_sb.ptr + sb_index;
      sb_index = from_sb.len;
      return partial_where;
    }

  *bufp = buffer_start + BEFORE_SIZE;

  if (partial_size)
    {
      memmove (buffer_start + BEFORE_SIZE, partial_where,
	      (unsigned int) partial_size);
      memcpy (buffer_start + BEFORE_SIZE, save_source, AFTER_SIZE);
    }
  limit = input_file_give_next_buffer (buffer_start
				       + BEFORE_SIZE
				       + partial_size);
  if (limit)
    {
      register char *p;		/* Find last newline.  */
      /* Terminate the buffer to avoid confusing TC_EOL_IN_INSN.  */
      *limit = '\0';
      for (p = limit - 1; *p != '\n' || TC_EOL_IN_INSN (p); --p)
	;
      ++p;

      while (p <= buffer_start + BEFORE_SIZE)
	{
	  int limoff;

	  limoff = limit - buffer_start;
	  buffer_length += input_file_buffer_size ();
	  buffer_start = xrealloc (buffer_start,
				   (BEFORE_SIZE
				    + 2 * buffer_length
				    + AFTER_SIZE));
	  *bufp = buffer_start + BEFORE_SIZE;
	  limit = input_file_give_next_buffer (buffer_start + limoff);

	  if (limit == NULL)
	    {
	      as_warn (_("partial line at end of file ignored"));
	      partial_where = NULL;
	      if (next_saved_file)
		*bufp = input_scrub_pop (next_saved_file);
	      return NULL;
	    }

	  /* Terminate the buffer to avoid confusing TC_EOL_IN_INSN.  */
	  *limit = '\0';
	  for (p = limit - 1; *p != '\n' || TC_EOL_IN_INSN (p); --p)
	    ;
	  ++p;
	}

      partial_where = p;
      partial_size = limit - p;
      memcpy (save_source, partial_where, (int) AFTER_SIZE);
      memcpy (partial_where, AFTER_STRING, (int) AFTER_SIZE);
    }
  else
    {
      partial_where = 0;
      if (partial_size > 0)
	{
	  as_warn (_("partial line at end of file ignored"));
	}

      /* Tell the listing we've finished the file.  */
      LISTING_EOF ();

      /* If we should pop to another file at EOF, do it.  */
      if (next_saved_file)
	{
	  *bufp = input_scrub_pop (next_saved_file);	/* Pop state */
	  /* partial_where is now correct to return, since we popped it.  */
	}
    }
  return (partial_where);
}