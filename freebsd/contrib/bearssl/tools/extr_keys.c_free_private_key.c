#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* x; } ;
struct TYPE_8__ {TYPE_4__* iq; TYPE_4__* dq; TYPE_4__* dp; TYPE_4__* q; TYPE_4__* p; } ;
struct TYPE_9__ {TYPE_1__ ec; TYPE_2__ rsa; } ;
struct TYPE_10__ {int key_type; TYPE_3__ key; } ;
typedef  TYPE_4__ private_key ;

/* Variables and functions */
#define  BR_KEYTYPE_EC 129 
#define  BR_KEYTYPE_RSA 128 
 int /*<<< orphan*/  xfree (TYPE_4__*) ; 

void
free_private_key(private_key *sk)
{
	if (sk == NULL) {
		return;
	}
	switch (sk->key_type) {
	case BR_KEYTYPE_RSA:
		xfree(sk->key.rsa.p);
		xfree(sk->key.rsa.q);
		xfree(sk->key.rsa.dp);
		xfree(sk->key.rsa.dq);
		xfree(sk->key.rsa.iq);
		break;
	case BR_KEYTYPE_EC:
		xfree(sk->key.ec.x);
		break;
	}
	xfree(sk);
}