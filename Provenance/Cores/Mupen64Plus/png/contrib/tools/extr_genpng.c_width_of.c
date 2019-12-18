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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char*) ; 
 double strtod (char const*,char**) ; 

__attribute__((used)) static double
width_of(const char *arg)
{
   if (strcmp(arg, "filled") == 0)
      return 0;

   else
   {
      char *ep = NULL;
      double w = strtod(arg, &ep);

      if (ep != NULL && *ep == 0 && w > 0)
         return w;
   }

   fprintf(stderr, "genpng: invalid line width %s\n", arg);
   exit(1);
}