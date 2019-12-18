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
struct socket {struct sock* sk; } ;
struct sock {int dummy; } ;
struct atm_vcc {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 struct atm_vcc* ATM_SD (struct socket*) ; 
 int /*<<< orphan*/  ATM_VF_READY ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,struct atm_vcc*) ; 
 int /*<<< orphan*/  svc_disconnect (struct atm_vcc*) ; 
 int /*<<< orphan*/  vcc_release (struct socket*) ; 

__attribute__((used)) static int svc_release(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct atm_vcc *vcc;

	if (sk)  {
		vcc = ATM_SD(sock);
		pr_debug("svc_release %p\n", vcc);
		clear_bit(ATM_VF_READY, &vcc->flags);
		/* VCC pointer is used as a reference, so we must not free it
		   (thereby subjecting it to re-use) before all pending connections
		   are closed */
		svc_disconnect(vcc);
		vcc_release(sock);
	}
	return 0;
}