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
struct macro_buffer {int is_identifier; } ;

/* Variables and functions */
 scalar_t__ is_digit (char) ; 
 scalar_t__ is_identifier_nondigit (char) ; 
 int /*<<< orphan*/  set_token (struct macro_buffer*,char*,char*) ; 

__attribute__((used)) static int
get_identifier (struct macro_buffer *tok, char *p, char *end)
{
  if (p < end
      && is_identifier_nondigit (*p))
    {
      char *tok_start = p;

      while (p < end
             && (is_identifier_nondigit (*p)
                 || is_digit (*p)))
        p++;

      set_token (tok, tok_start, p);
      tok->is_identifier = 1;
      return 1;
    }
  else
    return 0;
}