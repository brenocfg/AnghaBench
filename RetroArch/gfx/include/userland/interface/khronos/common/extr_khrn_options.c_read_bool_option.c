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
 char* getenv (char const*) ; 

__attribute__((used)) static bool read_bool_option(const char *name, bool cur)
{
   char *val = getenv(name);

   if (val == NULL)
      return cur;

   if (val[0] == 't' || val[0] == 'T' || val[0] == '1')
      return true;

   return false;
}