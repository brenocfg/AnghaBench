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
struct rose_sock {unsigned short va; unsigned short vs; } ;

/* Variables and functions */
 unsigned short ROSE_MODULUS ; 
 struct rose_sock* rose_sk (struct sock*) ; 

int rose_validate_nr(struct sock *sk, unsigned short nr)
{
	struct rose_sock *rose = rose_sk(sk);
	unsigned short vc = rose->va;

	while (vc != rose->vs) {
		if (nr == vc) return 1;
		vc = (vc + 1) % ROSE_MODULUS;
	}

	return nr == rose->vs;
}