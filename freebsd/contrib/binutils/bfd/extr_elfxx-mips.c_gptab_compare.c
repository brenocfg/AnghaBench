#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int gt_g_value; } ;
struct TYPE_4__ {TYPE_1__ gt_entry; } ;
typedef  TYPE_2__ Elf32_gptab ;

/* Variables and functions */

__attribute__((used)) static int
gptab_compare (const void *p1, const void *p2)
{
  const Elf32_gptab *a1 = p1;
  const Elf32_gptab *a2 = p2;

  return a1->gt_entry.gt_g_value - a2->gt_entry.gt_g_value;
}