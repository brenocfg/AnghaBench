#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sin6_addr; scalar_t__ sin6_port; int /*<<< orphan*/  sin6_family; } ;
union sctp_addr {TYPE_1__ v6; } ;
struct sock {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rcv_saddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 TYPE_2__* inet6_sk (struct sock*) ; 

__attribute__((used)) static void sctp_v6_from_sk(union sctp_addr *addr, struct sock *sk)
{
	addr->v6.sin6_family = AF_INET6;
	addr->v6.sin6_port = 0;
	addr->v6.sin6_addr = inet6_sk(sk)->rcv_saddr;
}