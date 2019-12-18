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
 int FALSE ; 
 scalar_t__ ISALNUM (char const) ; 
 int TRUE ; 

__attribute__((used)) static bool peek_ipv6(const char *str, size_t *skip)
{
  /*
   * Scan for a potential IPv6 literal.
   * - Valid globs contain a hyphen and <= 1 colon.
   * - IPv6 literals contain no hyphens and >= 2 colons.
   */
  size_t i = 0;
  size_t colons = 0;
  if(str[i++] != '[') {
    return FALSE;
  }
  for(;;) {
    const char c = str[i++];
    if(ISALNUM(c) || c == '.' || c == '%') {
      /* ok */
    }
    else if(c == ':') {
      colons++;
    }
    else if(c == ']') {
      *skip = i;
      return colons >= 2 ? TRUE : FALSE;
    }
    else {
      return FALSE;
    }
  }
}