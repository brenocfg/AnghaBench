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
struct TYPE_2__ {int ordinal; } ;
typedef  TYPE_1__ export_type ;

/* Variables and functions */

__attribute__((used)) static int
pfunc (const void *a, const void *b)
{
  export_type *ap = *(export_type **) a;
  export_type *bp = *(export_type **) b;
  if (ap->ordinal == bp->ordinal)
    return 0;

  /* Unset ordinals go to the bottom.  */
  if (ap->ordinal == -1)
    return 1;
  if (bp->ordinal == -1)
    return -1;
  return (ap->ordinal - bp->ordinal);
}