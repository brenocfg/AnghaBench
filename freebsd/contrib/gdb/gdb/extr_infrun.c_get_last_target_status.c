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
struct target_waitstatus {int dummy; } ;
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 int /*<<< orphan*/  target_last_wait_ptid ; 
 struct target_waitstatus target_last_waitstatus ; 

void
get_last_target_status (ptid_t *ptidp, struct target_waitstatus *status)
{
  *ptidp = target_last_wait_ptid;
  *status = target_last_waitstatus;
}