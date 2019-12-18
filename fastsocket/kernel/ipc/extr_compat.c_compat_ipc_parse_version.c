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
 int IPC_64 ; 

__attribute__((used)) static inline int compat_ipc_parse_version(int *cmd)
{
	int version = *cmd & IPC_64;

	/* this is tricky: architectures that have support for the old
	 * ipc structures in 64 bit binaries need to have IPC_64 set
	 * in cmd, the others need to have it cleared */
#ifndef ipc_parse_version
	*cmd |= IPC_64;
#else
	*cmd &= ~IPC_64;
#endif
	return version;
}