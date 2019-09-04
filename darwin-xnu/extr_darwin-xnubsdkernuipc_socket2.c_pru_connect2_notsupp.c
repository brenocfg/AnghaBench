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
 int EOPNOTSUPP ; 

int
pru_connect2_notsupp(struct socket *so1, struct socket *so2)
{
#pragma unused(so1, so2)
	return (EOPNOTSUPP);
}