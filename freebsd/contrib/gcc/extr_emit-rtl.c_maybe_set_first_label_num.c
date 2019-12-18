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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ CODE_LABEL_NUMBER (int /*<<< orphan*/ ) ; 
 scalar_t__ first_label_num ; 

void
maybe_set_first_label_num (rtx x)
{
  if (CODE_LABEL_NUMBER (x) < first_label_num)
    first_label_num = CODE_LABEL_NUMBER (x);
}