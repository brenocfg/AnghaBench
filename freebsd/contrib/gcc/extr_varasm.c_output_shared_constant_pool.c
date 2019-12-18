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
 int /*<<< orphan*/  output_constant_pool_contents (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shared_constant_pool ; 

void
output_shared_constant_pool (void)
{
  output_constant_pool_contents (shared_constant_pool);
}