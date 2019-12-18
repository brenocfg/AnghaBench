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
struct socket {int dummy; } ;
struct sockaddr {int dummy; } ;
struct proc {int dummy; } ;
struct TYPE_2__ {int (* pru_bind ) (struct socket*,struct sockaddr*,struct proc*) ;} ;

/* Variables and functions */
 TYPE_1__ raw_usrreqs ; 
 int stub1 (struct socket*,struct sockaddr*,struct proc*) ; 

__attribute__((used)) static int
key_bind(struct socket *so, struct sockaddr *nam, struct proc *p)
{
	int error;
	error = raw_usrreqs.pru_bind(so, nam, p); /* xxx just EINVAL */
	return error;
}