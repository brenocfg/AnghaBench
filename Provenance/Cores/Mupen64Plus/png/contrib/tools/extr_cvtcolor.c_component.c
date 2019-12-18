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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*,unsigned long) ; 
 int /*<<< orphan*/  stderr ; 
 unsigned long strtoul (char const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char const*) ; 

unsigned long
component(const char *prog, const char *arg, int issRGB)
{
   char *ep;
   unsigned long c = strtoul(arg, &ep, 0);

   if (ep <= arg || *ep || c > 65535 || (issRGB && c > 255))
   {
      fprintf(stderr, "%s: %s: invalid component value (%lu)\n", prog, arg, c);
      usage(prog);
   }

   return c;
}