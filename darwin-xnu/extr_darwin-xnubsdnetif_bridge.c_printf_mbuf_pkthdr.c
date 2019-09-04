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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ mbuf_t ;

/* Variables and functions */
 scalar_t__ VM_KERNEL_ADDRPERM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_nextpkt (scalar_t__) ; 
 int /*<<< orphan*/  mbuf_pkthdr_header (scalar_t__) ; 
 scalar_t__ mbuf_pkthdr_len (scalar_t__) ; 
 int /*<<< orphan*/  mbuf_pkthdr_rcvif (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 

void
printf_mbuf_pkthdr(mbuf_t m, const char *prefix, const char *suffix)
{
	if (m)
		printf("%spktlen: %u rcvif: 0x%llx header: 0x%llx "
		    "nextpkt: 0x%llx%s",
		    prefix ? prefix : "", (unsigned int)mbuf_pkthdr_len(m),
		    (uint64_t)VM_KERNEL_ADDRPERM(mbuf_pkthdr_rcvif(m)),
		    (uint64_t)VM_KERNEL_ADDRPERM(mbuf_pkthdr_header(m)),
		    (uint64_t)VM_KERNEL_ADDRPERM(mbuf_nextpkt(m)),
		    suffix ? suffix : "");
	else
		printf("%s<NULL>%s\n", prefix, suffix);
}