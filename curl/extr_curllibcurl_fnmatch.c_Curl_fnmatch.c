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
 int CURL_FNMATCH_FAIL ; 
 int loop (unsigned char*,unsigned char*,int) ; 

int Curl_fnmatch(void *ptr, const char *pattern, const char *string)
{
  (void)ptr; /* the argument is specified by the curl_fnmatch_callback
                prototype, but not used by Curl_fnmatch() */
  if(!pattern || !string) {
    return CURL_FNMATCH_FAIL;
  }
  return loop((unsigned char *)pattern, (unsigned char *)string, 2);
}