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
struct indexentry {scalar_t__ val; } ;

/* Variables and functions */

__attribute__((used)) static int
cmpindexentry (const void *a, const void *b)
{
  const struct indexentry *contestantA = a;
  const struct indexentry *contestantB = b;

  if (contestantA->val < contestantB->val)
    return -1;
  else if (contestantA->val > contestantB->val)
    return 1;
  else
    return 0;
}