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
struct uml_pt_regs {int dummy; } ;
struct faultinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEGV_IS_FIXABLE (struct faultinfo*) ; 
 struct faultinfo* UPT_FAULTINFO (struct uml_pt_regs*) ; 
 int /*<<< orphan*/  UPT_IP (struct uml_pt_regs*) ; 
 scalar_t__ UPT_IS_USER (struct uml_pt_regs*) ; 
 int /*<<< orphan*/  bad_segv (struct faultinfo,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  segv (struct faultinfo,int /*<<< orphan*/ ,scalar_t__,struct uml_pt_regs*) ; 

void segv_handler(int sig, struct uml_pt_regs *regs)
{
	struct faultinfo * fi = UPT_FAULTINFO(regs);

	if (UPT_IS_USER(regs) && !SEGV_IS_FIXABLE(fi)) {
		bad_segv(*fi, UPT_IP(regs));
		return;
	}
	segv(*fi, UPT_IP(regs), UPT_IS_USER(regs), regs);
}