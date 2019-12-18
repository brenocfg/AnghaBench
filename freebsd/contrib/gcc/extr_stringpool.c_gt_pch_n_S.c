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

/* Variables and functions */
 int /*<<< orphan*/  gt_pch_note_object (void*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gt_pch_p_S ; 
 int /*<<< orphan*/  gt_types_enum_last ; 

void
gt_pch_n_S (const void *x)
{
  gt_pch_note_object ((void *)x, (void *)x, &gt_pch_p_S,
		      gt_types_enum_last);
}