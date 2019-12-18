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
typedef  int /*<<< orphan*/  ptid_t ;
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;

/* Variables and functions */
 scalar_t__ MON_LSI ; 
 scalar_t__ mips_monitor ; 
 int /*<<< orphan*/  mips_receive_wait ; 
 int /*<<< orphan*/  mips_request (char,int,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mips_resume (ptid_t ptid, int step, enum target_signal siggnal)
{
  int err;

  /* LSI PMON requires returns a reply packet "0x1 s 0x0 0x57f" after
     a single step, so we wait for that.  */
  mips_request (step ? 's' : 'c', 1, siggnal,
		mips_monitor == MON_LSI && step ? &err : (int *) NULL,
		mips_receive_wait, NULL);
}