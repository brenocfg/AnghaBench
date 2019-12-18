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
 int /*<<< orphan*/  GC_SVC_NAME_VPNSERVER ; 
 int /*<<< orphan*/  ICO_CASCADE ; 
 int /*<<< orphan*/  InitProcessCallOnce () ; 
 int MsService (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  StartProcess ; 
 int /*<<< orphan*/  StopProcess ; 
 int UnixService (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VgUseStaticLink () ; 

int main(int argc, char *argv[])
{
	InitProcessCallOnce();

	VgUseStaticLink();

#ifdef	OS_WIN32

	return MsService(GC_SVC_NAME_VPNSERVER, StartProcess, StopProcess, ICO_CASCADE, argv[0]);
#else	// OS_WIN32
	return UnixService(argc, argv, "vpnserver", StartProcess, StopProcess);
#endif	// OS_WIN32
}