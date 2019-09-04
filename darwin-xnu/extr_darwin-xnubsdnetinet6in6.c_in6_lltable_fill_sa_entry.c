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
struct sockaddr_in6 {int sin6_len; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr6; } ;
struct llentry {TYPE_1__ r_l3addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in6*,int) ; 

__attribute__((used)) static void
in6_lltable_fill_sa_entry(const struct llentry *lle, struct sockaddr *sa)
{
	struct sockaddr_in6 *sin6;

	sin6 = (struct sockaddr_in6 *)(void *)sa;
	bzero(sin6, sizeof(*sin6));
	sin6->sin6_family = AF_INET6;
	sin6->sin6_len = sizeof(*sin6);
	sin6->sin6_addr = lle->r_l3addr.addr6;
}