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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 unsigned long strtoul (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
parse_color(char *arg, unsigned int *colors)
{
   unsigned int ncolors = 0;

   while (*arg && ncolors < 4)
   {
      char *ep = arg;

      unsigned long ul = strtoul(arg, &ep, 0);

      if (ul > 65535)
      {
         fprintf(stderr, "makepng --color=...'%s': too big\n", arg);
         exit(1);
      }

      if (ep == arg)
      {
         fprintf(stderr, "makepng --color=...'%s': not a valid color\n", arg);
         exit(1);
      }

      if (*ep) ++ep; /* skip a separator */
      arg = ep;

      colors[++ncolors] = (unsigned int)ul; /* checked above */
   }

   if (*arg)
   {
      fprintf(stderr, "makepng --color=...'%s': too many values\n", arg);
      exit(1);
   }

   *colors = ncolors;
}