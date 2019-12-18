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
struct comparison {TYPE_1__* file; struct comparison* parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  stat; } ;

/* Variables and functions */
 scalar_t__ same_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
dir_loop (struct comparison const *cmp, int i)
{
  struct comparison const *p = cmp;
  while ((p = p->parent))
    if (0 < same_file (&p->file[i].stat, &cmp->file[i].stat))
      return true;
  return false;
}