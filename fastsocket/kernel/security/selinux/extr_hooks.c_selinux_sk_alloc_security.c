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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int sk_alloc_security (struct sock*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selinux_sk_alloc_security(struct sock *sk, int family, gfp_t priority)
{
	return sk_alloc_security(sk, family, priority);
}