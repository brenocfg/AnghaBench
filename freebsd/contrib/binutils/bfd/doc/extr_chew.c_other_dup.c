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
 int /*<<< orphan*/  catstr (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  check_range () ; 
 int /*<<< orphan*/  init_string (scalar_t__) ; 
 int /*<<< orphan*/  pc ; 
 scalar_t__ tos ; 

__attribute__((used)) static void
other_dup ()
{
  tos++;
  check_range ();
  init_string (tos);
  catstr (tos, tos - 1);
  pc++;
}