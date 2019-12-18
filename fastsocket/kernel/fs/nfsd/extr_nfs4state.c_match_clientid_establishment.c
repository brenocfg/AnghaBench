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
struct nfs4_client {scalar_t__ cl_exchange_flags; } ;

/* Variables and functions */

__attribute__((used)) static inline int
match_clientid_establishment(struct nfs4_client *clp, bool use_exchange_id)
{
	bool has_exchange_flags = (clp->cl_exchange_flags != 0);
	return use_exchange_id == has_exchange_flags;
}