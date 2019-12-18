#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  cl_id; } ;
struct nfs4_client {int /*<<< orphan*/  cl_idhash; TYPE_1__ cl_clientid; int /*<<< orphan*/  cl_strhash; } ;

/* Variables and functions */
 unsigned int clientid_hashval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  renew_client (struct nfs4_client*) ; 
 int /*<<< orphan*/ * unconf_id_hashtbl ; 
 int /*<<< orphan*/ * unconf_str_hashtbl ; 

__attribute__((used)) static void
add_to_unconfirmed(struct nfs4_client *clp, unsigned int strhashval)
{
	unsigned int idhashval;

	list_add(&clp->cl_strhash, &unconf_str_hashtbl[strhashval]);
	idhashval = clientid_hashval(clp->cl_clientid.cl_id);
	list_add(&clp->cl_idhash, &unconf_id_hashtbl[idhashval]);
	renew_client(clp);
}