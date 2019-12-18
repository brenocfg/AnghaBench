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
 char* attr_string (char const*,int) ; 
 char* scan_comma_elt (char const**) ; 

__attribute__((used)) static char *
next_comma_elt (const char **pstr)
{
  const char *start;

  start = scan_comma_elt (pstr);

  if (start == NULL)
    return NULL;

  return attr_string (start, *pstr - start);
}