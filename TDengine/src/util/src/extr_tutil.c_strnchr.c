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
typedef  size_t int32_t ;

/* Variables and functions */

char *strnchr(char *haystack, char needle, int32_t len, bool skipquote) {
  for (int32_t i = 0; i < len; ++i) {

    // skip the needle in quote, jump to the end of quoted string
    if (skipquote && (haystack[i] == '\'' || haystack[i] == '"')) {
      char quote = haystack[i++];
      while(i < len && haystack[i++] != quote);
      if (i >= len) {
        return NULL;
      }
    }

    if (haystack[i] == needle) {
      return &haystack[i];
    }
  }

  return NULL;
}