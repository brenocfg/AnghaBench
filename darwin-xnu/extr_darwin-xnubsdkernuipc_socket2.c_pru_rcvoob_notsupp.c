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
struct mbuf {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 

int
pru_rcvoob_notsupp(struct socket *so, struct mbuf *m, int flags)
{
#pragma unused(so, m, flags)
	return (EOPNOTSUPP);
}