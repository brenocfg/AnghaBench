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

/* Variables and functions */
 scalar_t__ isalnum (int) ; 
 scalar_t__ isspace (int) ; 

__attribute__((used)) static int read_tok(char *tok, size_t toklen, const char **pstr, char sep)
{
   const char *str = *pstr;
   size_t n = 0;
   char ch;

   /* skip past any whitespace */
   while (str[0] && isspace((int)(str[0])))
      str++;

   while ((ch = *str) != '\0' &&
          ch != sep &&
          (isalnum((int)ch) || (ch == '_') || (ch == '*')) &&
          n != toklen-1)
   {
      tok[n++] = ch;
      str++;
   }

   /* did it work out? */
   if (ch == '\0' || ch == sep)
   {
      if (ch) str++; /* move to next token if not at end */
      /* yes */
      tok[n] = '\0';
      *pstr = str;
      return 1;
   }
   else
   {
      /* no */
      return 0;
   }
}