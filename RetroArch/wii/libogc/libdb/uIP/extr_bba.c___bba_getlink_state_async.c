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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  EXI_CHANNEL_0 ; 
 int /*<<< orphan*/  EXI_DEVICE_2 ; 
 scalar_t__ EXI_Lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXI_Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __linkstate () ; 

__attribute__((used)) static u32 __bba_getlink_state_async()
{
	u32 ret;

	if(EXI_Lock(EXI_CHANNEL_0,EXI_DEVICE_2,NULL)==0) return 0;
	ret = __linkstate();
	EXI_Unlock(EXI_CHANNEL_0);
	return ret;
}