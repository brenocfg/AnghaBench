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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  TOKEN_LIST ;

/* Variables and functions */

TOKEN_LIST *GetEthListEx(UINT *total_num_including_hidden, bool enum_normal, bool enum_rawip)
{

#if	defined(UNIX_LINUX)
	return GetEthListLinux(enum_normal, enum_rawip);
#elif	defined(UNIX_SOLARIS)
	return GetEthListSolaris();
#elif	defined(BRIDGE_PCAP)
	return GetEthListPcap();
#elif	defined(BRIDGE_BPF)
	return GetEthListBpf();
#else
	return NULL;
#endif

}