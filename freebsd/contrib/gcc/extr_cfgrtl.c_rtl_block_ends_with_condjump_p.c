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
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  BB_END (int /*<<< orphan*/ ) ; 
 int any_condjump_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
rtl_block_ends_with_condjump_p (basic_block bb)
{
  return any_condjump_p (BB_END (bb));
}