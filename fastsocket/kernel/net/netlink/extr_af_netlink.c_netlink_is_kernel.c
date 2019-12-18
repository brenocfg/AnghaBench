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
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int NETLINK_KERNEL_SOCKET ; 
 TYPE_1__* nlk_sk (struct sock*) ; 

__attribute__((used)) static inline int netlink_is_kernel(struct sock *sk)
{
	return nlk_sk(sk)->flags & NETLINK_KERNEL_SOCKET;
}