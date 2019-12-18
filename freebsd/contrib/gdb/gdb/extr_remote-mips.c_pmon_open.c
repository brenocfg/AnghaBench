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
 int /*<<< orphan*/  MON_PMON ; 
 int /*<<< orphan*/  common_open (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pmon_ops ; 

__attribute__((used)) static void
pmon_open (char *name, int from_tty)
{
  common_open (&pmon_ops, name, from_tty, MON_PMON, "PMON> ");
}