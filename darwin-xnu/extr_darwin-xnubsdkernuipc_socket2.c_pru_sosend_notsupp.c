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
struct uio {int dummy; } ;
struct socket {int dummy; } ;
struct sockaddr {int dummy; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 

int
pru_sosend_notsupp(struct socket *so, struct sockaddr *addr, struct uio *uio,
    struct mbuf *top, struct mbuf *control, int flags)
{
#pragma unused(so, addr, uio, top, control, flags)
	return (EOPNOTSUPP);
}