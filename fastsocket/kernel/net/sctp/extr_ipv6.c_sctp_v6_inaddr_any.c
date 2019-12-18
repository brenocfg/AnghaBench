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
struct TYPE_2__ {int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; } ;
union sctp_addr {TYPE_1__ v6; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  memset (union sctp_addr*,int,int) ; 

__attribute__((used)) static void sctp_v6_inaddr_any(union sctp_addr *addr, __be16 port)
{
	memset(addr, 0x00, sizeof(union sctp_addr));
	addr->v6.sin6_family = AF_INET6;
	addr->v6.sin6_port = port;
}