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
 int /*<<< orphan*/  set_token (struct macro_buffer*,char*,char*) ; 

__attribute__((used)) static int
get_comment (struct macro_buffer *tok, char *p, char *end)
{
  if (p + 2 > end)
    return 0;
  else if (p[0] == '/'
           && p[1] == '*')
    {
      char *tok_start = p;

      p += 2;

      for (; p < end; p++)
        if (p + 2 <= end
            && p[0] == '*'
            && p[1] == '/')
          {
            p += 2;
            set_token (tok, tok_start, p);
            return 1;
          }

      error ("Unterminated comment in macro expansion.");
    }
  else if (p[0] == '/'
           && p[1] == '/')
    {
      char *tok_start = p;

      p += 2;
      for (; p < end; p++)
        if (*p == '\n')
          break;

      set_token (tok, tok_start, p);
      return 1;
    }
  else
    return 0;
}