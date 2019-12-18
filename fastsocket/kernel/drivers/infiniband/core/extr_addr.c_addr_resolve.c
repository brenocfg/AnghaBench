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
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct rdma_dev_addr {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int addr4_resolve (struct sockaddr_in*,struct sockaddr_in*,struct rdma_dev_addr*) ; 
 int addr6_resolve (struct sockaddr_in6*,struct sockaddr_in6*,struct rdma_dev_addr*) ; 

__attribute__((used)) static int addr_resolve(struct sockaddr *src_in,
			struct sockaddr *dst_in,
			struct rdma_dev_addr *addr)
{
	if (src_in->sa_family == AF_INET) {
		return addr4_resolve((struct sockaddr_in *) src_in,
			(struct sockaddr_in *) dst_in, addr);
	} else
		return addr6_resolve((struct sockaddr_in6 *) src_in,
			(struct sockaddr_in6 *) dst_in, addr);
}