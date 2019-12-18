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
typedef  int /*<<< orphan*/  type_var_p ;

/* Variables and functions */
 int tpa_next_partition (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int
type_var_next_partition (type_var_p tv, int i)
{
  return tpa_next_partition (tv, i);
}