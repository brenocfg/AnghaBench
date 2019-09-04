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
 scalar_t__ safeToLower (char const) ; 

__attribute__((used)) static int hasSuffixIgnoringCase(const char *string, const char *suffix)
{
  const char *stringPointer = string;
  const char *suffixPointer = suffix;

  if (suffix[0] == '\0')
  {
    return 1;
  }

  while (*stringPointer != '\0')
  {
    stringPointer++;
  }

  while (*suffixPointer != '\0')
  {
    suffixPointer++;
  }

  if (stringPointer - string < suffixPointer - suffix)
  {
    return 0;
  }

  while (safeToLower(*--suffixPointer) == safeToLower(*--stringPointer))
  {
    if (suffixPointer == suffix)
    {
      return 1;
    }
  }

  return 0;
}