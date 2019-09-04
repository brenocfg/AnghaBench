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
 char** Curl_month ; 
 int FALSE ; 
 int TRUE ; 
 scalar_t__ strcasecompare (char const*,char const* const) ; 

__attribute__((used)) static int checkmonth(const char *check)
{
  int i;
  const char * const *what;
  bool found = FALSE;

  what = &Curl_month[0];
  for(i = 0; i<12; i++) {
    if(strcasecompare(check, what[0])) {
      found = TRUE;
      break;
    }
    what++;
  }
  return found?i:-1; /* return the offset or -1, no real offset is -1 */
}