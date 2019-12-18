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
 int /*<<< orphan*/  gcc_assert (int) ; 
 int warn_strict_aliasing ; 

void
set_warn_strict_aliasing (int onoff)
{
  gcc_assert (onoff == 0 || onoff == 1);
  if (onoff != 0)
    warn_strict_aliasing = 3;
}