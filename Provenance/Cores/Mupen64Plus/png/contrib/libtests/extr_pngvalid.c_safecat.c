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

__attribute__((used)) static size_t safecat(char *buffer, size_t bufsize, size_t pos,
   const char *cat)
{
   while (pos < bufsize && cat != NULL && *cat != 0)
      buffer[pos++] = *cat++;

   if (pos >= bufsize)
      pos = bufsize-1;

   buffer[pos] = 0;
   return pos;
}