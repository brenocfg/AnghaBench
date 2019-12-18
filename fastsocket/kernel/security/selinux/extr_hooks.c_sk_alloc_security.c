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
struct sock {struct sk_security_struct* sk_security; } ;
struct sk_security_struct {void* sid; void* peer_sid; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 void* SECINITSID_UNLABELED ; 
 struct sk_security_struct* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selinux_netlbl_sk_security_reset (struct sk_security_struct*) ; 

__attribute__((used)) static int sk_alloc_security(struct sock *sk, int family, gfp_t priority)
{
	struct sk_security_struct *ssec;

	ssec = kzalloc(sizeof(*ssec), priority);
	if (!ssec)
		return -ENOMEM;

	ssec->peer_sid = SECINITSID_UNLABELED;
	ssec->sid = SECINITSID_UNLABELED;
	sk->sk_security = ssec;

	selinux_netlbl_sk_security_reset(ssec);

	return 0;
}