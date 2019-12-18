#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  partition_struct ;
struct TYPE_4__ {size_t condtrue; } ;
typedef  TYPE_1__ filter_struct ;
struct TYPE_5__ {int /*<<< orphan*/ * partition; } ;

/* Variables and functions */
 TYPE_3__* Cs2Area ; 

partition_struct * Cs2GetPartition(filter_struct * curfilter)
{
  // go through various filter conditions here(fix me)

  return &Cs2Area->partition[curfilter->condtrue];
}