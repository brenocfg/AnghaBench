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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ Result ;

/* Variables and functions */
 scalar_t__ IPC_Desc_StaticBuffer (scalar_t__,int) ; 
 scalar_t__ IPC_MakeHeader (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ R_SUCCEEDED (scalar_t__) ; 
 scalar_t__* getThreadCommandBuffer () ; 
 int /*<<< orphan*/  hbldrHandle ; 
 scalar_t__ svcSendSyncRequest (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Result HBLDR_SetArgv(const void* buffer, u32 size)
{
	u32* cmdbuf = getThreadCommandBuffer();

	cmdbuf[0] = IPC_MakeHeader(3, 0, 2); //0x30002
	cmdbuf[1] = IPC_Desc_StaticBuffer(size, 1);
	cmdbuf[2] = (u32)buffer;

	Result rc = svcSendSyncRequest(hbldrHandle);
	if (R_SUCCEEDED(rc)) rc = cmdbuf[1];
	return rc;
}