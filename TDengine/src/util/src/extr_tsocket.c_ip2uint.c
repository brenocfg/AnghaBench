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
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const* const) ; 

unsigned int ip2uint(const char *const ip_addr) {
  char ip_addr_cpy[20];
  char ip[5];

  strcpy(ip_addr_cpy, ip_addr);

  char *s_start, *s_end;
  s_start = ip_addr_cpy;
  s_end = ip_addr_cpy;

  int k;

  for (k = 0; *s_start != '\0'; s_start = s_end) {
    for (s_end = s_start; *s_end != '.' && *s_end != '\0'; s_end++) {
    }
    if (*s_end == '.') {
      *s_end = '\0';
      s_end++;
    }
    ip[k++] = (char)atoi(s_start);
  }

  ip[k] = '\0';

  return *((unsigned int *)ip);
}