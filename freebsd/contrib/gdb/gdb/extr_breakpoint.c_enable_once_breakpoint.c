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
struct breakpoint {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  disp_disable ; 
 int /*<<< orphan*/  do_enable_breakpoint (struct breakpoint*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
enable_once_breakpoint (struct breakpoint *bpt)
{
  do_enable_breakpoint (bpt, disp_disable);
}