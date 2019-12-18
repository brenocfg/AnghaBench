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
typedef  unsigned long png_uint_32 ;

/* Variables and functions */
 unsigned long FORMAT_COUNT ; 
 int /*<<< orphan*/ * format_names ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 unsigned long strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static png_uint_32
formatof(const char *arg)
{
   char *ep;
   unsigned long format = strtoul(arg, &ep, 0);

   if (ep > arg && *ep == 0 && format < FORMAT_COUNT)
      return (png_uint_32)format;

   else for (format=0; format < FORMAT_COUNT; ++format)
   {
      if (strcmp(format_names[format], arg) == 0)
         return (png_uint_32)format;
   }

   fprintf(stderr, "pngstest: format name '%s' invalid\n", arg);
   return FORMAT_COUNT;
}