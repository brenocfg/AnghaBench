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
 int processing_explicit_instantiation ; 

void
end_explicit_instantiation (void)
{
  gcc_assert (processing_explicit_instantiation);
  processing_explicit_instantiation = false;
}