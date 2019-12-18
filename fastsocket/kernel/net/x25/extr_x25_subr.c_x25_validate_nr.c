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
struct x25_sock {unsigned short va; unsigned short vs; TYPE_1__* neighbour; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {scalar_t__ extended; } ;

/* Variables and functions */
 int X25_EMODULUS ; 
 int X25_SMODULUS ; 
 struct x25_sock* x25_sk (struct sock*) ; 

int x25_validate_nr(struct sock *sk, unsigned short nr)
{
	struct x25_sock *x25 = x25_sk(sk);
	unsigned short vc = x25->va;
	int modulus = x25->neighbour->extended ? X25_EMODULUS : X25_SMODULUS;

	while (vc != x25->vs) {
		if (nr == vc)
			return 1;
		vc = (vc + 1) % modulus;
	}

	return nr == x25->vs ? 1 : 0;
}