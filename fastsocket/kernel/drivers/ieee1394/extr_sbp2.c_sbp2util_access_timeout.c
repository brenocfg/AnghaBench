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
struct sbp2_lu {scalar_t__ access_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbp2_access_wq ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int sbp2util_access_timeout(struct sbp2_lu *lu, int timeout)
{
	long leftover;

	leftover = wait_event_interruptible_timeout(
			sbp2_access_wq, lu->access_complete, timeout);
	lu->access_complete = 0;
	return leftover <= 0;
}