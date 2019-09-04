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
typedef  union in_addr_4_6 {int dummy; } in_addr_4_6 ;
struct net_port_info {scalar_t__ npi_if_index; scalar_t__ npi_local_port; scalar_t__ npi_foreign_port; scalar_t__ npi_owner_pid; scalar_t__ npi_effective_pid; scalar_t__ npi_flags; int /*<<< orphan*/  npi_foreign_addr_; int /*<<< orphan*/  npi_local_addr_; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool
net_port_info_equal(const struct net_port_info *x,
    const struct net_port_info *y)
{
	ASSERT(x != NULL && y != NULL);

	if (x->npi_if_index == y->npi_if_index &&
	    x->npi_local_port == y->npi_local_port &&
	    x->npi_foreign_port == y->npi_foreign_port &&
	    x->npi_owner_pid == y->npi_owner_pid &&
	    x->npi_effective_pid == y->npi_effective_pid &&
	    x->npi_flags == y->npi_flags &&
	    memcmp(&x->npi_local_addr_, &y->npi_local_addr_,
	        sizeof(union in_addr_4_6)) == 0 &&
	    memcmp(&x->npi_foreign_addr_, &y->npi_foreign_addr_,
	        sizeof(union in_addr_4_6)) == 0) {
		return (true);
	}
	return (false);
}