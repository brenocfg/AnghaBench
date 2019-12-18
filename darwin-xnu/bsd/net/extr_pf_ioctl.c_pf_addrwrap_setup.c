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
struct pf_addr_wrap {int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY (struct pf_addr_wrap*) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
pf_addrwrap_setup(struct pf_addr_wrap *aw)
{
	VERIFY(aw);
	bzero(&aw->p, sizeof aw->p);
}