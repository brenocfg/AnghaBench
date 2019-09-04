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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  kqueue_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_INFO_CALL_PIDINFO ; 
 int /*<<< orphan*/  PROC_PIDLISTDYNKQUEUES ; 
 int __proc_info (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
proc_list_dynkqueueids(int pid, kqueue_id_t *buf, uint32_t bufsz)
{
	return __proc_info(PROC_INFO_CALL_PIDINFO, pid, PROC_PIDLISTDYNKQUEUES, 0,
			buf, bufsz);
}