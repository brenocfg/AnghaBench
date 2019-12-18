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
 int FNM_NOMATCH ; 

int rl_fnmatch(const char *pattern, const char *string, int flags)
{
   int rv;
   const char *c = NULL;
   int charmatch = 0;

   for (c = pattern; *c != '\0'; c++)
   {
      /* String ended before pattern */
      if ((*c != '*') && (*string == '\0'))
         return FNM_NOMATCH;

      switch (*c)
      {
         /* Match any number of unknown chars */
         case '*':
            /* Find next node in the pattern
             * ignoring multiple asterixes
             */
            do {
               c++;
               if (*c == '\0')
                  return 0;
            } while (*c == '*');

            /* Match the remaining pattern
             * ignoring more and more characters. */
            do {
               /* We reached the end of the string without a
                * match. There is a way to optimize this by
                * calculating the minimum chars needed to
                * match the remaining pattern but I don't
                * think it is worth the work ATM.
                */
               if (*string == '\0')
                  return FNM_NOMATCH;

               rv = rl_fnmatch(c, string, flags);
               string++;
            } while (rv != 0);

            return 0;
            /* Match char from list */
         case '[':
            charmatch = 0;
            for (c++; *c != ']'; c++)
            {
               /* Bad format */
               if (*c == '\0')
                  return FNM_NOMATCH;

               /* Match already found */
               if (charmatch)
                  continue;

               if (*c == *string)
                  charmatch = 1;
            }

            /* No match in list */
            if (!charmatch)
               return FNM_NOMATCH;

            string++;
            break;
            /* Has any character */
         case '?':
            string++;
            break;
            /* Match following character verbatim */
         case '\\':
            c++;
            /* Dangling escape at end of pattern.
             * FIXME: Was c == '\0' (makes no sense).
             * Not sure if c == NULL or *c == '\0'
             * is intended. Assuming *c due to c++ right before. */
            if (*c == '\0')
               return FNM_NOMATCH;
         default:
            if (*c != *string)
               return FNM_NOMATCH;
            string++;
      }
   }

   /* End of string and end of pattend */
   if (*string == '\0')
      return 0;
   return FNM_NOMATCH;
}