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
typedef  scalar_t__ u8 ;
struct sock {int dummy; } ;
struct hybla {int hybla_en; } ;

/* Variables and functions */
 scalar_t__ TCP_CA_Open ; 
 struct hybla* inet_csk_ca (struct sock*) ; 

__attribute__((used)) static void hybla_state(struct sock *sk, u8 ca_state)
{
	struct hybla *ca = inet_csk_ca(sk);
	ca->hybla_en = (ca_state == TCP_CA_Open);
}