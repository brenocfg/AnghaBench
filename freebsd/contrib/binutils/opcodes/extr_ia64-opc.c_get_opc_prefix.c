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
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void
get_opc_prefix (const char **ptr, char *dest)
{
  char *c = strchr (*ptr, '.');
  if (c != NULL)
    {
      memcpy (dest, *ptr, c - *ptr);
      dest[c - *ptr] = '\0';
      *ptr = c + 1;
    }
  else
    {
      int l = strlen (*ptr);
      memcpy (dest, *ptr, l);
      dest[l] = '\0';
      *ptr += l;
    }
}