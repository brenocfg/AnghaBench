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
struct ndrv_cb {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ndrv_do_detach (struct ndrv_cb*) ; 
 struct ndrv_cb* sotondrvcb (struct socket*) ; 

__attribute__((used)) static int
ndrv_detach(struct socket *so)
{
	struct ndrv_cb *np = sotondrvcb(so);

	if (np == 0)
		return EINVAL;
	return ndrv_do_detach(np);
}