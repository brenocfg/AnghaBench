#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pi; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ PF_MAX_RETRIES ; 
 int /*<<< orphan*/  STAT_BUSY ; 
 int STAT_ERR ; 
 int /*<<< orphan*/  do_pf_write_start ; 
 int /*<<< orphan*/  next_request (int /*<<< orphan*/ ) ; 
 TYPE_1__* pf_current ; 
 scalar_t__ pf_retries ; 
 int pf_wait (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  pi_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pi_do_claimed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_pf_write_done(void)
{
	if (pf_wait(pf_current, STAT_BUSY, 0, "write block", "done") & STAT_ERR) {
		pi_disconnect(pf_current->pi);
		if (pf_retries < PF_MAX_RETRIES) {
			pf_retries++;
			pi_do_claimed(pf_current->pi, do_pf_write_start);
			return;
		}
		next_request(-EIO);
		return;
	}
	pi_disconnect(pf_current->pi);
	next_request(0);
}