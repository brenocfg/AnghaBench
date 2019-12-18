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
 scalar_t__ strtol (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool int_string(char *str, int *val)
{
   char *endptr = NULL;
   if (!str)
      return false;

   *val = (int) strtol(str, &endptr, 0);
   return ((*str != '\0') && (*endptr == '\0'));
}