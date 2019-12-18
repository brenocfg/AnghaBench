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
struct sock {int dummy; } ;
struct raw_sock {int /*<<< orphan*/  filter; } ;
struct TYPE_2__ {scalar_t__ num; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_ICMP ; 
 TYPE_1__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct raw_sock* raw_sk (struct sock*) ; 

__attribute__((used)) static int raw_init(struct sock *sk)
{
	struct raw_sock *rp = raw_sk(sk);

	if (inet_sk(sk)->num == IPPROTO_ICMP)
		memset(&rp->filter, 0, sizeof(rp->filter));
	return 0;
}