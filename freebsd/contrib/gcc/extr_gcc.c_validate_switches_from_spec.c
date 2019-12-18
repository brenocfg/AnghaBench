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
 char* validate_switches (char const*) ; 

__attribute__((used)) static inline void
validate_switches_from_spec (const char *spec)
{
  const char *p = spec;
  char c;
  while ((c = *p++))
    if (c == '%' && (*p == '{' || *p == '<' || (*p == 'W' && *++p == '{')))
      /* We have a switch spec.  */
      p = validate_switches (p + 1);
}