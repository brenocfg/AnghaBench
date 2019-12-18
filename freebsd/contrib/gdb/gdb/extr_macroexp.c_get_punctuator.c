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
 int /*<<< orphan*/  memcmp (char*,char const*,int) ; 
 int /*<<< orphan*/  set_token (struct macro_buffer*,char*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
get_punctuator (struct macro_buffer *tok, char *p, char *end)
{
  /* Here, speed is much less important than correctness and clarity.  */

  /* ISO/IEC 9899:1999 (E)  Section 6.4.6  Paragraph 1  */
  static const char * const punctuators[] = {
    "[", "]", "(", ")", "{", "}", ".", "->", 
    "++", "--", "&", "*", "+", "-", "~", "!",
    "/", "%", "<<", ">>", "<", ">", "<=", ">=", "==", "!=", 
    "^", "|", "&&", "||",
    "?", ":", ";", "...",
    "=", "*=", "/=", "%=", "+=", "-=", "<<=", ">>=", "&=", "^=", "|=",
    ",", "#", "##",
    "<:", ":>", "<%", "%>", "%:", "%:%:",
    0
  };

  int i;

  if (p + 1 <= end)
    {
      for (i = 0; punctuators[i]; i++)
        {
          const char *punctuator = punctuators[i];

          if (p[0] == punctuator[0])
            {
              int len = strlen (punctuator);

              if (p + len <= end
                  && ! memcmp (p, punctuator, len))
                {
                  set_token (tok, p, p + len);
                  return 1;
                }
            }
        }
    }

  return 0;
}