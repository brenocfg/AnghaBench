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
 size_t countof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * recognised_schemes ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool recognise_scheme(const char *scheme)
{
   size_t ii;

   if (!scheme)
      return false;

   for (ii = 0; ii < countof(recognised_schemes); ii++)
   {
      if (strcmp(recognised_schemes[ii], scheme) == 0)
         return true;
   }

   return false;
}