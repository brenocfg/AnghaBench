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
struct nfs4_client_reclaim {int /*<<< orphan*/  cr_recdir; int /*<<< orphan*/  cr_strhash; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEXDIR_LEN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct nfs4_client_reclaim* alloc_reclaim () ; 
 unsigned int clientstr_hashval (char const*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * reclaim_str_hashtbl ; 
 int /*<<< orphan*/  reclaim_str_hashtbl_size ; 

int
nfs4_client_to_reclaim(const char *name)
{
	unsigned int strhashval;
	struct nfs4_client_reclaim *crp = NULL;

	dprintk("NFSD nfs4_client_to_reclaim NAME: %.*s\n", HEXDIR_LEN, name);
	crp = alloc_reclaim();
	if (!crp)
		return 0;
	strhashval = clientstr_hashval(name);
	INIT_LIST_HEAD(&crp->cr_strhash);
	list_add(&crp->cr_strhash, &reclaim_str_hashtbl[strhashval]);
	memcpy(crp->cr_recdir, name, HEXDIR_LEN);
	reclaim_str_hashtbl_size++;
	return 1;
}