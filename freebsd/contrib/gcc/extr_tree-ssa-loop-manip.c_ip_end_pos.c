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
struct loop {int /*<<< orphan*/  latch; } ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */

basic_block
ip_end_pos (struct loop *loop)
{
  return loop->latch;
}