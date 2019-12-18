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
struct deplist {int len; scalar_t__* deps; } ;

/* Variables and functions */

__attribute__((used)) static int
deplist_equals (struct deplist *d1, struct deplist *d2)
{
  int i;

  if (d1->len != d2->len)
    return 0;

  for (i = 0; i < d1->len; i++)
    if (d1->deps[i] != d2->deps[i])
      return 0;

  return 1;
}