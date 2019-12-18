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
struct veno {int basertt; int inc; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 struct veno* inet_csk_ca (struct sock*) ; 
 int /*<<< orphan*/  veno_enable (struct sock*) ; 

__attribute__((used)) static void tcp_veno_init(struct sock *sk)
{
	struct veno *veno = inet_csk_ca(sk);

	veno->basertt = 0x7fffffff;
	veno->inc = 1;
	veno_enable(sk);
}