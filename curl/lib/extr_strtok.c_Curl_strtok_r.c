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
 scalar_t__ strchr (char const*,char) ; 

char *
Curl_strtok_r(char *ptr, const char *sep, char **end)
{
  if(!ptr)
    /* we got NULL input so then we get our last position instead */
    ptr = *end;

  /* pass all letters that are including in the separator string */
  while(*ptr && strchr(sep, *ptr))
    ++ptr;

  if(*ptr) {
    /* so this is where the next piece of string starts */
    char *start = ptr;

    /* set the end pointer to the first byte after the start */
    *end = start + 1;

    /* scan through the string to find where it ends, it ends on a
       null byte or a character that exists in the separator string */
    while(**end && !strchr(sep, **end))
      ++*end;

    if(**end) {
      /* the end is not a null byte */
      **end = '\0';  /* zero terminate it! */
      ++*end;        /* advance the last pointer to beyond the null byte */
    }

    return start; /* return the position where the string starts */
  }

  /* we ended up on a null byte, there are no more strings to find! */
  return NULL;
}