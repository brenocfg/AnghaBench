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
struct bfa_ioc {int /*<<< orphan*/  ioc_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_IOC_TOV ; 
 int /*<<< orphan*/  bfa_ioc_send_getattr (struct bfa_ioc*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_sm_getattr_entry(struct bfa_ioc *ioc)
{
	mod_timer(&ioc->ioc_timer, jiffies +
		msecs_to_jiffies(BFA_IOC_TOV));
	bfa_ioc_send_getattr(ioc);
}