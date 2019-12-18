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
 int /*<<< orphan*/ * AllocSysMemory (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CDVD_IRX ; 
 int /*<<< orphan*/  CDVD_rpc_server ; 
 int /*<<< orphan*/  GetThreadId () ; 
 int /*<<< orphan*/  SleepThread () ; 
 int /*<<< orphan*/ * buffer ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  qd ; 
 int /*<<< orphan*/  sceSifInitRpc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceSifRegisterRpc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sceSifRpcLoop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sceSifSetRpcQueue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd0 ; 

void CDVD_Thread(void *param)
{
#ifdef DEBUG
    printf("CDVD: RPC Initialize\n");
#endif

    sceSifInitRpc(0);

    // 0x4800 bytes for TocEntry structures (can fit 128 of them)
    // 0x400 bytes for the filename string
    buffer = AllocSysMemory(0, 0x4C00, NULL);
    if (buffer == NULL) {
#ifdef DEBUG
        printf("Failed to allocate memory for RPC buffer!\n");
#endif

        SleepThread();
    }

    sceSifSetRpcQueue(&qd, GetThreadId());
    sceSifRegisterRpc(&sd0, CDVD_IRX, CDVD_rpc_server, (void *)buffer, 0, 0, &qd);
    sceSifRpcLoop(&qd);
}