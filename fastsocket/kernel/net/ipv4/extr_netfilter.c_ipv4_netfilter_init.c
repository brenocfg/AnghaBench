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

/* Variables and functions */
 int /*<<< orphan*/  nf_ip_afinfo ; 
 int nf_register_afinfo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipv4_netfilter_init(void)
{
	return nf_register_afinfo(&nf_ip_afinfo);
}