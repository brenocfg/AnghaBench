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
struct sock {int dummy; } ;
struct dn_scp {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ DN_CI ; 
 struct dn_scp* DN_SK (struct sock*) ; 
 int /*<<< orphan*/  NSP_RCI ; 
 int /*<<< orphan*/  dn_nsp_send_conninit (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dn_nsp_retrans_conninit(struct sock *sk)
{
	struct dn_scp *scp = DN_SK(sk);

	if (scp->state == DN_CI)
		dn_nsp_send_conninit(sk, NSP_RCI);

	return 0;
}