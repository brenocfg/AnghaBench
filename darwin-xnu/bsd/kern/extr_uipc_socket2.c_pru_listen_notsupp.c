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
struct proc {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 

int
pru_listen_notsupp(struct socket *so, struct proc *p)
{
#pragma unused(so, p)
	return (EOPNOTSUPP);
}