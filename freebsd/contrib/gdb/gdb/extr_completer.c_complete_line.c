#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cmd_list_element {char** (* completer ) (char*,char*) ;scalar_t__ enums; int /*<<< orphan*/  allow_unknown; struct cmd_list_element** prefixlist; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* la_word_break_characters ) () ;} ;

/* Variables and functions */
 scalar_t__ alloca (int) ; 
 struct cmd_list_element* cmdlist ; 
 char** complete_on_cmdlist (struct cmd_list_element*,char*,char*) ; 
 char** complete_on_enum (scalar_t__,char*,char*) ; 
 TYPE_1__* current_language ; 
 char** filename_completer (char*,char*) ; 
 int /*<<< orphan*/  gdb_completer_command_word_break_characters ; 
 int /*<<< orphan*/  gdb_completer_file_name_break_characters ; 
 scalar_t__ isalnum (char) ; 
 char** location_completer (char*,char*) ; 
 struct cmd_list_element* lookup_cmd_1 (char**,struct cmd_list_element*,struct cmd_list_element**,int) ; 
 int /*<<< orphan*/  rl_completer_word_break_characters ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ ,char) ; 
 char* strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 () ; 
 char** stub2 (char*,char*) ; 
 char** stub3 (char*,char*) ; 

char **
complete_line (const char *text, char *line_buffer, int point)
{
  char **list = NULL;
  char *tmp_command, *p;
  /* Pointer within tmp_command which corresponds to text.  */
  char *word;
  struct cmd_list_element *c, *result_list;

  /* Choose the default set of word break characters to break completions.
     If we later find out that we are doing completions on command strings
     (as opposed to strings supplied by the individual command completer
     functions, which can be any string) then we will switch to the
     special word break set for command strings, which leaves out the
     '-' character used in some commands.  */

  rl_completer_word_break_characters =
    current_language->la_word_break_characters();

      /* Decide whether to complete on a list of gdb commands or on symbols. */
  tmp_command = (char *) alloca (point + 1);
  p = tmp_command;

  strncpy (tmp_command, line_buffer, point);
  tmp_command[point] = '\0';
  /* Since text always contains some number of characters leading up
     to point, we can find the equivalent position in tmp_command
     by subtracting that many characters from the end of tmp_command.  */
  word = tmp_command + point - strlen (text);

  if (point == 0)
    {
      /* An empty line we want to consider ambiguous; that is, it
	 could be any command.  */
      c = (struct cmd_list_element *) -1;
      result_list = 0;
    }
  else
    {
      c = lookup_cmd_1 (&p, cmdlist, &result_list, 1);
    }

  /* Move p up to the next interesting thing.  */
  while (*p == ' ' || *p == '\t')
    {
      p++;
    }

  if (!c)
    {
      /* It is an unrecognized command.  So there are no
	 possible completions.  */
      list = NULL;
    }
  else if (c == (struct cmd_list_element *) -1)
    {
      char *q;

      /* lookup_cmd_1 advances p up to the first ambiguous thing, but
	 doesn't advance over that thing itself.  Do so now.  */
      q = p;
      while (*q && (isalnum (*q) || *q == '-' || *q == '_'))
	++q;
      if (q != tmp_command + point)
	{
	  /* There is something beyond the ambiguous
	     command, so there are no possible completions.  For
	     example, "info t " or "info t foo" does not complete
	     to anything, because "info t" can be "info target" or
	     "info terminal".  */
	  list = NULL;
	}
      else
	{
	  /* We're trying to complete on the command which was ambiguous.
	     This we can deal with.  */
	  if (result_list)
	    {
	      list = complete_on_cmdlist (*result_list->prefixlist, p,
					  word);
	    }
	  else
	    {
	      list = complete_on_cmdlist (cmdlist, p, word);
	    }
	  /* Insure that readline does the right thing with respect to
	     inserting quotes.  */
	  rl_completer_word_break_characters =
	    gdb_completer_command_word_break_characters;
	}
    }
  else
    {
      /* We've recognized a full command.  */

      if (p == tmp_command + point)
	{
	  /* There is no non-whitespace in the line beyond the command.  */

	  if (p[-1] == ' ' || p[-1] == '\t')
	    {
	      /* The command is followed by whitespace; we need to complete
		 on whatever comes after command.  */
	      if (c->prefixlist)
		{
		  /* It is a prefix command; what comes after it is
		     a subcommand (e.g. "info ").  */
		  list = complete_on_cmdlist (*c->prefixlist, p, word);

		  /* Insure that readline does the right thing
		         with respect to inserting quotes.  */
		  rl_completer_word_break_characters =
		    gdb_completer_command_word_break_characters;
		}
	      else if (c->enums)
		{
		  list = complete_on_enum (c->enums, p, word);
		  rl_completer_word_break_characters =
		    gdb_completer_command_word_break_characters;
		}
	      else
		{
		  /* It is a normal command; what comes after it is
		     completed by the command's completer function.  */
		  if (c->completer == filename_completer)
		    {
		      /* Many commands which want to complete on
			 file names accept several file names, as
			 in "run foo bar >>baz".  So we don't want
			 to complete the entire text after the
			 command, just the last word.  To this
			 end, we need to find the beginning of the
			 file name by starting at `word' and going
			 backwards.  */
		      for (p = word;
			   p > tmp_command
			     && strchr (gdb_completer_file_name_break_characters, p[-1]) == NULL;
			   p--)
			;
		      rl_completer_word_break_characters =
			gdb_completer_file_name_break_characters;
		    }
		  else if (c->completer == location_completer)
		    {
		      /* Commands which complete on locations want to
			 see the entire argument.  */
		      for (p = word;
			   p > tmp_command
			     && p[-1] != ' ' && p[-1] != '\t';
			   p--)
			;
		    }
		  list = (*c->completer) (p, word);
		}
	    }
	  else
	    {
	      /* The command is not followed by whitespace; we need to
		 complete on the command itself.  e.g. "p" which is a
		 command itself but also can complete to "print", "ptype"
		 etc.  */
	      char *q;

	      /* Find the command we are completing on.  */
	      q = p;
	      while (q > tmp_command)
		{
		  if (isalnum (q[-1]) || q[-1] == '-' || q[-1] == '_')
		    --q;
		  else
		    break;
		}

	      list = complete_on_cmdlist (result_list, q, word);

		  /* Insure that readline does the right thing
		     with respect to inserting quotes.  */
	      rl_completer_word_break_characters =
		gdb_completer_command_word_break_characters;
	    }
	}
      else
	{
	  /* There is non-whitespace beyond the command.  */

	  if (c->prefixlist && !c->allow_unknown)
	    {
	      /* It is an unrecognized subcommand of a prefix command,
		 e.g. "info adsfkdj".  */
	      list = NULL;
	    }
	  else if (c->enums)
	    {
	      list = complete_on_enum (c->enums, p, word);
	    }
	  else
	    {
	      /* It is a normal command.  */
	      if (c->completer == filename_completer)
		{
		  /* See the commentary above about the specifics
		     of file-name completion.  */
		  for (p = word;
		       p > tmp_command
			 && strchr (gdb_completer_file_name_break_characters, p[-1]) == NULL;
		       p--)
		    ;
		  rl_completer_word_break_characters =
		    gdb_completer_file_name_break_characters;
		}
	      else if (c->completer == location_completer)
		{
		  for (p = word;
		       p > tmp_command
			 && p[-1] != ' ' && p[-1] != '\t';
		       p--)
		    ;
		}
	      list = (*c->completer) (p, word);
	    }
	}
    }

  return list;
}