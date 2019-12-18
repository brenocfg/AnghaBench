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
struct color {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int color_count ; 
 struct color const* colors ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static const struct color *
color_of(const char *arg)
{
   int icolor = color_count;

   while (--icolor >= 0)
   {
      if (strcmp(colors[icolor].name, arg) == 0)
         return colors+icolor;
   }

   fprintf(stderr, "genpng: invalid color %s\n", arg);
   exit(1);
}