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
 int /*<<< orphan*/  TYPE_MAX_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ host_integerp (int /*<<< orphan*/ ,int) ; 
 int offset_limit ; 
 int /*<<< orphan*/  sizetype ; 
 int tree_low_cst (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
init_offset_limit (void)
{
  if (host_integerp (TYPE_MAX_VALUE (sizetype), 1))
    offset_limit = tree_low_cst (TYPE_MAX_VALUE (sizetype), 1);
  else
    offset_limit = -1;
  offset_limit /= 2;
}