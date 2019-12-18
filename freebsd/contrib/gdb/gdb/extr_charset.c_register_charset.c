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
struct charset {struct charset* next; } ;

/* Variables and functions */
 struct charset* all_charsets ; 

__attribute__((used)) static void
register_charset (struct charset *cs)
{
  struct charset **ptr;

  /* Put the new charset on the end, so that the list ends up in the
     same order as the registrations in the _initialize function.  */
  for (ptr = &all_charsets; *ptr; ptr = &(*ptr)->next)
    ;

  cs->next = 0;
  *ptr = cs;
}