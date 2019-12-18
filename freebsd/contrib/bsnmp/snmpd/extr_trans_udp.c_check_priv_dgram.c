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
struct sockcred {scalar_t__ sc_euid; } ;
struct port_input {int priv; } ;

/* Variables and functions */

__attribute__((used)) static void
check_priv_dgram(struct port_input *pi, struct sockcred *cred)
{

	/* process explicitly sends credentials */
	if (cred)
		pi->priv = (cred->sc_euid == 0);
	else
		pi->priv = 0;
}