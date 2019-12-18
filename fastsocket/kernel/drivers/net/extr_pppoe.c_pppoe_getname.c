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
struct socket {int /*<<< orphan*/  sk; } ;
struct sockaddr {int dummy; } ;
struct TYPE_3__ {struct sockaddr pppoe; } ;
struct sockaddr_pppox {TYPE_1__ sa_addr; int /*<<< orphan*/  sa_protocol; int /*<<< orphan*/  sa_family; } ;
struct pppoe_addr {int dummy; } ;
struct TYPE_4__ {struct sockaddr_pppox pppoe_pa; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_PPPOX ; 
 int /*<<< orphan*/  PX_PROTO_OE ; 
 int /*<<< orphan*/  memcpy (struct sockaddr*,struct sockaddr_pppox*,int) ; 
 TYPE_2__* pppox_sk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pppoe_getname(struct socket *sock, struct sockaddr *uaddr,
		  int *usockaddr_len, int peer)
{
	int len = sizeof(struct sockaddr_pppox);
	struct sockaddr_pppox sp;

	sp.sa_family	= AF_PPPOX;
	sp.sa_protocol	= PX_PROTO_OE;
	memcpy(&sp.sa_addr.pppoe, &pppox_sk(sock->sk)->pppoe_pa,
	       sizeof(struct pppoe_addr));

	memcpy(uaddr, &sp, len);

	*usockaddr_len = len;

	return 0;
}