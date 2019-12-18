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
struct diff3_block {struct diff3_block* next; } ;

/* Variables and functions */

__attribute__((used)) static struct diff3_block *
reverse_diff3_blocklist (struct diff3_block *diff)
{
  register struct diff3_block *tmp, *next, *prev;

  for (tmp = diff, prev = 0;  tmp;  tmp = next)
    {
      next = tmp->next;
      tmp->next = prev;
      prev = tmp;
    }

  return prev;
}