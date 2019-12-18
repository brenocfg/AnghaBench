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
 int /*<<< orphan*/  make_numeric_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min_attr_value (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static rtx
min_fn (rtx exp)
{
  int unknown;
  return make_numeric_value (min_attr_value (exp, &unknown));
}