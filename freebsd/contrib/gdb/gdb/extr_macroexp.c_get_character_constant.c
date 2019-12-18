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
struct macro_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_escape (char**) ; 
 int /*<<< orphan*/  set_token (struct macro_buffer*,char*,char*) ; 

__attribute__((used)) static int
get_character_constant (struct macro_buffer *tok, char *p, char *end)
{
  /* ISO/IEC 9899:1999 (E)  Section 6.4.4.4  paragraph 1 
     But of course, what really matters is that we handle it the same
     way GDB's C/C++ lexer does.  So we call parse_escape in utils.c
     to handle escape sequences.  */
  if ((p + 1 <= end && *p == '\'')
      || (p + 2 <= end && p[0] == 'L' && p[1] == '\''))
    {
      char *tok_start = p;
      char *body_start;

      if (*p == '\'')
        p++;
      else if (*p == 'L')
        p += 2;
      else
        gdb_assert (0);

      body_start = p;
      for (;;)
        {
          if (p >= end)
            error ("Unmatched single quote.");
          else if (*p == '\'')
            {
              if (p == body_start)
                error ("A character constant must contain at least one "
                       "character.");
              p++;
              break;
            }
          else if (*p == '\\')
            {
              p++;
              parse_escape (&p);
            }
          else
            p++;
        }

      set_token (tok, tok_start, p);
      return 1;
    }
  else
    return 0;
}