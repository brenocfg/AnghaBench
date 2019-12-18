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
 char* clean_text_base ; 

__attribute__((used)) static int
identify_lineno (const char *clean_p)
{
  int line_num = 1;
  const char *scan_p;

  for (scan_p = clean_text_base; scan_p <= clean_p; scan_p++)
    if (*scan_p == '\n')
      line_num++;
  return line_num;
}