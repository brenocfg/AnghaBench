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
struct TYPE_2__ {int /*<<< orphan*/  (* la_word_break_characters ) () ;} ;

/* Variables and functions */
 char** complete_line (char const*,char*,int) ; 
 TYPE_1__* current_language ; 
 int /*<<< orphan*/  rl_completer_word_break_characters ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  xfree (char**) ; 

__attribute__((used)) static char *
line_completion_function (const char *text, int matches, char *line_buffer, int point)
{
  static char **list = (char **) NULL;	/* Cache of completions */
  static int index;		/* Next cached completion */
  char *output = NULL;

  if (matches == 0)
    {
      /* The caller is beginning to accumulate a new set of completions, so
         we need to find all of them now, and cache them for returning one at
         a time on future calls. */

      if (list)
	{
	  /* Free the storage used by LIST, but not by the strings inside.
	     This is because rl_complete_internal () frees the strings. */
	  xfree (list);
	}
      index = 0;
      list = complete_line (text, line_buffer, point);
    }

  /* If we found a list of potential completions during initialization then
     dole them out one at a time.  The vector of completions is NULL
     terminated, so after returning the last one, return NULL (and continue
     to do so) each time we are called after that, until a new list is
     available. */

  if (list)
    {
      output = list[index];
      if (output)
	{
	  index++;
	}
    }

#if 0
  /* Can't do this because readline hasn't yet checked the word breaks
     for figuring out whether to insert a quote.  */
  if (output == NULL)
    /* Make sure the word break characters are set back to normal for the
       next time that readline tries to complete something.  */
    rl_completer_word_break_characters =
      current_language->la_word_break_characters();
#endif

  return (output);
}