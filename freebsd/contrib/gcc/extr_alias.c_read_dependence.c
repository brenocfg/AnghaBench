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
 scalar_t__ MEM_VOLATILE_P (int /*<<< orphan*/ ) ; 

int
read_dependence (rtx mem, rtx x)
{
  return MEM_VOLATILE_P (x) && MEM_VOLATILE_P (mem);
}