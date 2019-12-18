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
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 char* realloc (char*,int) ; 
 int strlen (char*) ; 
 char* strncat (char*,char const*,int) ; 

__attribute__((used)) static char *
str_append (char *dest, const char *input, int len)
{  
  char *new_dest;
  int oldlen;

  if (len == 0)
    return dest;
  /* printf("str_append: <<%s>>, <<%s>>, %d\n", dest, input, len); */
  oldlen = (dest ? strlen(dest) : 0);
  new_dest = realloc (dest, oldlen + len + 1);
  memset (new_dest + oldlen, 0, len + 1);
  return strncat (new_dest, input, len);
}