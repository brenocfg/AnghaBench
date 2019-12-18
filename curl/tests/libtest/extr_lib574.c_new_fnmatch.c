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
 int CURL_FNMATCHFUNC_MATCH ; 

__attribute__((used)) static int new_fnmatch(void *ptr,
                       const char *pattern, const char *string)
{
  (void)ptr;
  (void)pattern;
  (void)string;
  return CURL_FNMATCHFUNC_MATCH;
}