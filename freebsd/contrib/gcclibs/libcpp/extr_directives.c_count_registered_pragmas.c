#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct pragma_entry* space; } ;
struct pragma_entry {TYPE_1__ u; scalar_t__ is_nspace; struct pragma_entry* next; } ;

/* Variables and functions */

__attribute__((used)) static int
count_registered_pragmas (struct pragma_entry *pe)
{
  int ct = 0;
  for (; pe != NULL; pe = pe->next)
    {
      if (pe->is_nspace)
	ct += count_registered_pragmas (pe->u.space);
      ct++;
    }
  return ct;
}