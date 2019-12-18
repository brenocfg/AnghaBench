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
typedef  TYPE_1__* shared_bitmap_info_t ;
struct TYPE_2__ {int /*<<< orphan*/  pt_vars; } ;

/* Variables and functions */
 int bitmap_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
shared_bitmap_eq (const void *p1, const void *p2)
{
  const shared_bitmap_info_t sbi1 = (shared_bitmap_info_t) p1;
  const shared_bitmap_info_t sbi2 = (shared_bitmap_info_t) p2;
  return bitmap_equal_p (sbi1->pt_vars, sbi2->pt_vars);
}