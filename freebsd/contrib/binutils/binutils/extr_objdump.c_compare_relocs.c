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
struct TYPE_2__ {scalar_t__ address; } ;
typedef  TYPE_1__ arelent ;

/* Variables and functions */

__attribute__((used)) static int
compare_relocs (const void *ap, const void *bp)
{
  const arelent *a = * (const arelent **) ap;
  const arelent *b = * (const arelent **) bp;

  if (a->address > b->address)
    return 1;
  else if (a->address < b->address)
    return -1;

  /* So that associated relocations tied to the same address show up
     in the correct order, we don't do any further sorting.  */
  if (a > b)
    return 1;
  else if (a < b)
    return -1;
  else
    return 0;
}