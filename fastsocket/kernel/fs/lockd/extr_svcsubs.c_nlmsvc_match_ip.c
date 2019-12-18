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
struct nlm_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nlm_srcaddr (struct nlm_host*) ; 
 int rpc_cmp_addr (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int
nlmsvc_match_ip(void *datap, struct nlm_host *host)
{
	return rpc_cmp_addr(nlm_srcaddr(host), datap);
}