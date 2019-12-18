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
struct set_of_data {int /*<<< orphan*/  found; int /*<<< orphan*/  pat; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ reg_overlap_mentioned_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rtx_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_of_1 (rtx x, rtx pat, void *data1)
{
   struct set_of_data *data = (struct set_of_data *) (data1);
   if (rtx_equal_p (x, data->pat)
       || (!MEM_P (x) && reg_overlap_mentioned_p (data->pat, x)))
     data->found = pat;
}