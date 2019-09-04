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
typedef  int /*<<< orphan*/  ETH ;

/* Variables and functions */

ETH *OpenEth(char *name, bool local, bool tapmode, char *tapaddr)
{

#if	defined(UNIX_LINUX)
	return OpenEthLinux(name, local, tapmode, tapaddr);
#elif	defined(UNIX_BSD)
	return OpenEthBSD(name, local, tapmode, tapaddr);
#elif	defined(UNIX_SOLARIS)
	return OpenEthSolaris(name, local, tapmode, tapaddr);
#elif	defined(BRIDGE_PCAP)
	return OpenEthPcap(name, local, tapmode, tapaddr);
#elif	defined(BRIDGE_BPF)
	return OpenEthBpf(name, local, tapmode, tapaddr);
#else
	return NULL;
#endif

}