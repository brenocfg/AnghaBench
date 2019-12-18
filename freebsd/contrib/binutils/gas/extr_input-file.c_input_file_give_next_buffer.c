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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_SIZE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int do_scrub_chars (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * f_in ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_name ; 
 int fread (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_file_get ; 
 scalar_t__ preprocess ; 
 int /*<<< orphan*/  xstrerror (int /*<<< orphan*/ ) ; 

char *
input_file_give_next_buffer (char *where /* Where to place 1st character of new buffer.  */)
{
  char *return_value;		/* -> Last char of what we read, + 1.  */
  register int size;

  if (f_in == (FILE *) 0)
    return 0;
  /* fflush (stdin); could be done here if you want to synchronise
     stdin and stdout, for the case where our input file is stdin.
     Since the assembler shouldn't do any output to stdout, we
     don't bother to synch output and input.  */
  if (preprocess)
    size = do_scrub_chars (input_file_get, where, BUFFER_SIZE);
  else
    size = fread (where, sizeof (char), BUFFER_SIZE, f_in);
  if (size < 0)
    {
      as_bad (_("can't read from %s: %s"), file_name, xstrerror (errno));
      size = 0;
    }
  if (size)
    return_value = where + size;
  else
    {
      if (fclose (f_in))
	as_warn (_("can't close %s: %s"), file_name, xstrerror (errno));

      f_in = (FILE *) 0;
      return_value = 0;
    }

  return return_value;
}