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
 int /*<<< orphan*/  VX_BREAK_ADD ; 
 int net_break (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vx_insert_breakpoint (int addr)
{
  return net_break (addr, VX_BREAK_ADD);
}