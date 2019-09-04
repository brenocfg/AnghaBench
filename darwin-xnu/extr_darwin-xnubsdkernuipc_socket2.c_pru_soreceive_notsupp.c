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
pru_soreceive_notsupp(struct socket *so, struct sockaddr **paddr,
    struct uio *uio, struct mbuf **mp0, struct mbuf **controlp, int *flagsp)
{
#pragma unused(so, paddr, uio, mp0, controlp, flagsp)
	return (EOPNOTSUPP);
}