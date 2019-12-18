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
typedef  int time_t ;

/* Variables and functions */
 int PARSEDATE_OK ; 
 int parsedate (char const*,int*) ; 

time_t curl_getdate(const char *p, const time_t *now)
{
  time_t parsed = -1;
  int rc = parsedate(p, &parsed);
  (void)now; /* legacy argument from the past that we ignore */

  if(rc == PARSEDATE_OK) {
    if(parsed == -1)
      /* avoid returning -1 for a working scenario */
      parsed++;
    return parsed;
  }
  /* everything else is fail */
  return -1;
}