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
struct iclass {int /*<<< orphan*/  name; scalar_t__ is_class; } ;

/* Variables and functions */
 struct iclass** ics ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sub_compare (const void *e1, const void *e2)
{
  struct iclass *ic1 = ics[*(int *)e1];
  struct iclass *ic2 = ics[*(int *)e2];

  if (ic1->is_class)
    {
      if (!ic2->is_class)
        return -1;
    }
  else if (ic2->is_class)
    return 1;

  return strcmp (ic1->name, ic2->name);
}