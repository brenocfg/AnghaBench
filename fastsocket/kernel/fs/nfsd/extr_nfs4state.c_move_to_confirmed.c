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
struct nfs4_client {int /*<<< orphan*/  cl_strhash; int /*<<< orphan*/  cl_recdir; int /*<<< orphan*/  cl_idhash; TYPE_1__ cl_clientid; } ;

/* Variables and functions */
 unsigned int clientid_hashval (int /*<<< orphan*/ ) ; 
 unsigned int clientstr_hashval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * conf_id_hashtbl ; 
 int /*<<< orphan*/ * conf_str_hashtbl ; 
 int /*<<< orphan*/  dprintk (char*,struct nfs4_client*) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  renew_client (struct nfs4_client*) ; 

__attribute__((used)) static void
move_to_confirmed(struct nfs4_client *clp)
{
	unsigned int idhashval = clientid_hashval(clp->cl_clientid.cl_id);
	unsigned int strhashval;

	dprintk("NFSD: move_to_confirm nfs4_client %p\n", clp);
	list_move(&clp->cl_idhash, &conf_id_hashtbl[idhashval]);
	strhashval = clientstr_hashval(clp->cl_recdir);
	list_move(&clp->cl_strhash, &conf_str_hashtbl[strhashval]);
	renew_client(clp);
}