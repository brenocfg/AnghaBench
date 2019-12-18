#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ sa_family; } ;
union sctp_addr {TYPE_1__ sa; } ;
struct sctp_sock {scalar_t__ v4mapped; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  sctp_v4_map_v6 (union sctp_addr*) ; 

__attribute__((used)) static void sctp_v6_addr_v4map(struct sctp_sock *sp, union sctp_addr *addr)
{
	if (sp->v4mapped && AF_INET == addr->sa.sa_family)
		sctp_v4_map_v6(addr);
}