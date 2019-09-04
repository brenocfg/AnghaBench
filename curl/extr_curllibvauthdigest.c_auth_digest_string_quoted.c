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
 char* malloc (size_t) ; 

__attribute__((used)) static char *auth_digest_string_quoted(const char *source)
{
  char *dest;
  const char *s = source;
  size_t n = 1; /* null terminator */

  /* Calculate size needed */
  while(*s) {
    ++n;
    if(*s == '"' || *s == '\\') {
      ++n;
    }
    ++s;
  }

  dest = malloc(n);
  if(dest) {
    char *d = dest;
    s = source;
    while(*s) {
      if(*s == '"' || *s == '\\') {
        *d++ = '\\';
      }
      *d++ = *s++;
    }
    *d = 0;
  }

  return dest;
}