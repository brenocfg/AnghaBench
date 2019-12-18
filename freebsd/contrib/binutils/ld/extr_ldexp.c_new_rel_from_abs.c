#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ bfd_vma ;
struct TYPE_4__ {TYPE_2__* section; int /*<<< orphan*/ * str; scalar_t__ value; int /*<<< orphan*/  valid_p; } ;
struct TYPE_6__ {TYPE_2__* section; TYPE_1__ result; } ;
struct TYPE_5__ {scalar_t__ vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__ expld ; 

__attribute__((used)) static void
new_rel_from_abs (bfd_vma value)
{
  expld.result.valid_p = TRUE;
  expld.result.value = value - expld.section->vma;
  expld.result.str = NULL;
  expld.result.section = expld.section;
}