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
struct symlist {int dummy; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  FOPEN_RT ; 
 int /*<<< orphan*/  IS_LINE_TERMINATOR (char) ; 
 scalar_t__ IS_WHITESPACE (char) ; 
 int TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_specific_symbol (char*,struct symlist**) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int get_file_size (char const*) ; 
 int /*<<< orphan*/  non_fatal (int /*<<< orphan*/ ,char const*,unsigned int) ; 
 int status ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 char* xmalloc (int) ; 

__attribute__((used)) static void
add_specific_symbols (const char *filename, struct symlist **list)
{
  off_t  size;
  FILE * f;
  char * line;
  char * buffer;
  unsigned int line_count;

  size = get_file_size (filename);
  if (size == 0)
    {
      status = 1;
      return;
    }

  buffer = xmalloc (size + 2);
  f = fopen (filename, FOPEN_RT);
  if (f == NULL)
    fatal (_("cannot open '%s': %s"), filename, strerror (errno));

  if (fread (buffer, 1, size, f) == 0 || ferror (f))
    fatal (_("%s: fread failed"), filename);

  fclose (f);
  buffer [size] = '\n';
  buffer [size + 1] = '\0';

  line_count = 1;

  for (line = buffer; * line != '\0'; line ++)
    {
      char * eol;
      char * name;
      char * name_end;
      int finished = FALSE;

      for (eol = line;; eol ++)
	{
	  switch (* eol)
	    {
	    case '\n':
	      * eol = '\0';
	      /* Cope with \n\r.  */
	      if (eol[1] == '\r')
		++ eol;
	      finished = TRUE;
	      break;

	    case '\r':
	      * eol = '\0';
	      /* Cope with \r\n.  */
	      if (eol[1] == '\n')
		++ eol;
	      finished = TRUE;
	      break;

	    case 0:
	      finished = TRUE;
	      break;

	    case '#':
	      /* Line comment, Terminate the line here, in case a
		 name is present and then allow the rest of the
		 loop to find the real end of the line.  */
	      * eol = '\0';
	      break;

	    default:
	      break;
	    }

	  if (finished)
	    break;
	}

      /* A name may now exist somewhere between 'line' and 'eol'.
	 Strip off leading whitespace and trailing whitespace,
	 then add it to the list.  */
      for (name = line; IS_WHITESPACE (* name); name ++)
	;
      for (name_end = name;
	   (! IS_WHITESPACE (* name_end))
	   && (! IS_LINE_TERMINATOR (* name_end));
	   name_end ++)
	;

      if (! IS_LINE_TERMINATOR (* name_end))
	{
	  char * extra;

	  for (extra = name_end + 1; IS_WHITESPACE (* extra); extra ++)
	    ;

	  if (! IS_LINE_TERMINATOR (* extra))
	    non_fatal (_("%s:%d: Ignoring rubbish found on this line"),
		       filename, line_count);
	}

      * name_end = '\0';

      if (name_end > name)
	add_specific_symbol (name, list);

      /* Advance line pointer to end of line.  The 'eol ++' in the for
	 loop above will then advance us to the start of the next line.  */
      line = eol;
      line_count ++;
    }
}