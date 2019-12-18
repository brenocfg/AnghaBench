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
struct uml_pt_regs {int /*<<< orphan*/  faultinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_skas_faultinfo (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  segv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_segv(int pid, struct uml_pt_regs * regs)
{
	get_skas_faultinfo(pid, &regs->faultinfo);
	segv(regs->faultinfo, 0, 1, NULL);
}