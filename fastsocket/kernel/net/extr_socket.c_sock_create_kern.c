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
struct socket {int dummy; } ;

/* Variables and functions */
 int __sock_create (int /*<<< orphan*/ *,int,int,int,struct socket**,int) ; 
 int /*<<< orphan*/  init_net ; 

int sock_create_kern(int family, int type, int protocol, struct socket **res)
{
	return __sock_create(&init_net, family, type, protocol, res, 1);
}