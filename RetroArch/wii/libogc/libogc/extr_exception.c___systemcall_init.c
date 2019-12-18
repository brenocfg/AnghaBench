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
 int /*<<< orphan*/  EX_SYS_CALL ; 
 int /*<<< orphan*/  __exception_load (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ systemcallhandler_end ; 
 scalar_t__ systemcallhandler_start ; 

void __systemcall_init()
{
	__exception_load(EX_SYS_CALL,systemcallhandler_start,(systemcallhandler_end-systemcallhandler_start),NULL);
}