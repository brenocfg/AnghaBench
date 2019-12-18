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

__attribute__((used)) static void
mips_promote_ready (rtx *ready, int lower, int higher)
{
  rtx new_head;
  int i;

  new_head = ready[lower];
  for (i = lower; i < higher; i++)
    ready[i] = ready[i + 1];
  ready[i] = new_head;
}