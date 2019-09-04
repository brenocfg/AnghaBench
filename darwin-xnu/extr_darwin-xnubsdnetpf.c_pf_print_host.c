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
typedef  scalar_t__ u_int16_t ;
struct pf_addr {int dummy; } ;
typedef  int /*<<< orphan*/  sa_family_t ;

/* Variables and functions */
 int ntohs (scalar_t__) ; 
 int /*<<< orphan*/  pf_print_addr (struct pf_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
pf_print_host(struct pf_addr *addr, u_int16_t p, sa_family_t af)
{
	pf_print_addr(addr, af);
	if (p)
		printf("[%u]", ntohs(p));
}