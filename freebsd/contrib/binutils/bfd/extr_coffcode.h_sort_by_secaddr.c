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
struct TYPE_2__ {scalar_t__ vma; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */

__attribute__((used)) static int
sort_by_secaddr (const void * arg1, const void * arg2)
{
  const asection *a = *(const asection **) arg1;
  const asection *b = *(const asection **) arg2;

  if (a->vma < b->vma)
    return -1;
  else if (a->vma > b->vma)
    return 1;

  return 0;
}