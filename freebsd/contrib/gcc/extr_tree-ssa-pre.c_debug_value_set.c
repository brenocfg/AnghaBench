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
typedef  int /*<<< orphan*/  value_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  print_value_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  stderr ; 

void
debug_value_set (value_set_t set, const char *setname, int blockindex)
{
  print_value_set (stderr, set, setname, blockindex);
}