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
 scalar_t__ is_digit (char) ; 
 scalar_t__ is_identifier_nondigit (char) ; 
 int /*<<< orphan*/  set_token (struct macro_buffer*,char*,char*) ; 
 scalar_t__ strchr (char*,char) ; 

__attribute__((used)) static int
get_pp_number (struct macro_buffer *tok, char *p, char *end)
{
  if (p < end
      && (is_digit (*p)
          || *p == '.'))
    {
      char *tok_start = p;

      while (p < end)
        {
          if (is_digit (*p)
              || is_identifier_nondigit (*p)
              || *p == '.')
            p++;
          else if (p + 2 <= end
                   && strchr ("eEpP.", *p)
                   && (p[1] == '+' || p[1] == '-'))
            p += 2;
          else
            break;
        }

      set_token (tok, tok_start, p);
      return 1;
    }
  else
    return 0;
}