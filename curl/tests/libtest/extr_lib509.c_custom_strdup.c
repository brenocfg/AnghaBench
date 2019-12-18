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
typedef  char* strdup ;

/* Variables and functions */
 scalar_t__ seen_malloc ; 
 int seen_strdup ; 

char *custom_strdup(const char *ptr)
{
  if(!seen_strdup && seen_malloc) {
    /* currently (2013.03.13), memory tracking enabled builds do not call
       the strdup callback, in this case malloc callback and memcpy are used
       instead. If some day this is changed the following printf() should be
       uncommented, and a line added to test definition.
    printf("seen custom_strdup()\n");
    */
    seen_strdup = 1;
  }
  return (strdup)(ptr);
}