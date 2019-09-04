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
 int /*<<< orphan*/  PROC_INFO_CALL_UDATA_INFO ; 
 int __proc_info (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,void*,int) ; 

int
proc_udata_info(int pid, int flavor, void *buffer, int buffersize)
{
	return (__proc_info(PROC_INFO_CALL_UDATA_INFO, pid, flavor, 0, buffer, buffersize));
}