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
typedef  int /*<<< orphan*/  u_int ;
struct uio {int dummy; } ;
struct socket {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 

int
pru_sosend_list_notsupp(struct socket *so, struct uio **uio,
    u_int uiocnt, int flags)
{
#pragma unused(so, uio, uiocnt, flags)
	return (EOPNOTSUPP);
}