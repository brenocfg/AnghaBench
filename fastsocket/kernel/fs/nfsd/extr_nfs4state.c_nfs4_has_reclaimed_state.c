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
struct nfs4_client {int dummy; } ;

/* Variables and functions */
 unsigned int clientstr_hashval (char const*) ; 
 struct nfs4_client* find_confirmed_client_by_str (char const*,unsigned int,int) ; 

int
nfs4_has_reclaimed_state(const char *name, bool use_exchange_id)
{
	unsigned int strhashval = clientstr_hashval(name);
	struct nfs4_client *clp;

	clp = find_confirmed_client_by_str(name, strhashval, use_exchange_id);
	return clp ? 1 : 0;
}