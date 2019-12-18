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
struct nfs4_stateowner {int /*<<< orphan*/  so_id; int /*<<< orphan*/  so_stateids; } ;
struct TYPE_2__ {scalar_t__ si_generation; int /*<<< orphan*/  si_fileid; int /*<<< orphan*/  si_stateownerid; int /*<<< orphan*/  si_boot; } ;
struct nfs4_stateid {struct nfs4_stateid* st_openstp; int /*<<< orphan*/  st_deny_bmap; scalar_t__ st_access_bmap; TYPE_1__ st_stateid; struct nfs4_file* st_file; struct nfs4_stateowner* st_stateowner; int /*<<< orphan*/  st_perstateowner; int /*<<< orphan*/  st_perfile; int /*<<< orphan*/  st_hash; int /*<<< orphan*/  st_lockowners; } ;
struct nfs4_file {int /*<<< orphan*/  fi_id; int /*<<< orphan*/  fi_stateids; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  boot_time ; 
 int /*<<< orphan*/  get_nfs4_file (struct nfs4_file*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lockstateid_hashtbl ; 
 struct nfs4_stateid* nfs4_alloc_stateid () ; 
 unsigned int stateid_hashval (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nfs4_stateid *
alloc_init_lock_stateid(struct nfs4_stateowner *sop, struct nfs4_file *fp, struct nfs4_stateid *open_stp)
{
	struct nfs4_stateid *stp;
	unsigned int hashval = stateid_hashval(sop->so_id, fp->fi_id);

	stp = nfs4_alloc_stateid();
	if (stp == NULL)
		goto out;
	INIT_LIST_HEAD(&stp->st_hash);
	INIT_LIST_HEAD(&stp->st_perfile);
	INIT_LIST_HEAD(&stp->st_perstateowner);
	INIT_LIST_HEAD(&stp->st_lockowners); /* not used */
	list_add(&stp->st_hash, &lockstateid_hashtbl[hashval]);
	list_add(&stp->st_perfile, &fp->fi_stateids);
	list_add(&stp->st_perstateowner, &sop->so_stateids);
	stp->st_stateowner = sop;
	get_nfs4_file(fp);
	stp->st_file = fp;
	stp->st_stateid.si_boot = boot_time;
	stp->st_stateid.si_stateownerid = sop->so_id;
	stp->st_stateid.si_fileid = fp->fi_id;
	stp->st_stateid.si_generation = 0;
	stp->st_access_bmap = 0;
	stp->st_deny_bmap = open_stp->st_deny_bmap;
	stp->st_openstp = open_stp;

out:
	return stp;
}