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
typedef  size_t s32 ;

/* Variables and functions */
 int /*<<< orphan*/  LWP_ThreadBroadcast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _ioEXILock ; 

__attribute__((used)) static s32 __exi_unlock(s32 chn,s32 dev)
{
	LWP_ThreadBroadcast(_ioEXILock[chn]);
	return 1;
}