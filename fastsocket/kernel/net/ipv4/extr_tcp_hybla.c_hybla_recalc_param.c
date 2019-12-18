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
struct hybla {int rho_3ls; int rho; int rho2_7ls; int rho2; } ;
struct TYPE_2__ {int srtt; } ;

/* Variables and functions */
 struct hybla* inet_csk_ca (struct sock*) ; 
 int max_t (int /*<<< orphan*/ ,int,int) ; 
 int msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtt0 ; 
 TYPE_1__* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static inline void hybla_recalc_param (struct sock *sk)
{
	struct hybla *ca = inet_csk_ca(sk);

	ca->rho_3ls = max_t(u32, tcp_sk(sk)->srtt / msecs_to_jiffies(rtt0), 8);
	ca->rho = ca->rho_3ls >> 3;
	ca->rho2_7ls = (ca->rho_3ls * ca->rho_3ls) << 1;
	ca->rho2 = ca->rho2_7ls >>7;
}