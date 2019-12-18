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
 int strlen (char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static void
strcut (char *haystack, char *needle)
{
  haystack = strstr (haystack, needle);

  if (haystack)
    {
      char *src;

      for (src = haystack + strlen (needle); *src;)
	*haystack++ = *src++;

      *haystack = 0;
    }
}