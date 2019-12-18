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
typedef  int /*<<< orphan*/  stateid_t ;

/* Variables and functions */
 int CLIENT_HASH_SIZE ; 
 int FILE_HASH_SIZE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int LOCK_HASH_SIZE ; 
 int OWNER_HASH_SIZE ; 
 int SESSION_HASH_SIZE ; 
 int STATEID_HASH_SIZE ; 
 int /*<<< orphan*/  client_lru ; 
 int /*<<< orphan*/  close_lru ; 
 int /*<<< orphan*/ * conf_id_hashtbl ; 
 int /*<<< orphan*/ * conf_str_hashtbl ; 
 int /*<<< orphan*/  del_recall_lru ; 
 int /*<<< orphan*/ * file_hashtbl ; 
 int /*<<< orphan*/ * lock_ownerid_hashtbl ; 
 int /*<<< orphan*/ * lock_ownerstr_hashtbl ; 
 int /*<<< orphan*/ * lockstateid_hashtbl ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int nfsd4_init_slabs () ; 
 int /*<<< orphan*/  onestateid ; 
 int /*<<< orphan*/ * ownerid_hashtbl ; 
 int /*<<< orphan*/ * ownerstr_hashtbl ; 
 int /*<<< orphan*/ * reclaim_str_hashtbl ; 
 scalar_t__ reclaim_str_hashtbl_size ; 
 int /*<<< orphan*/ * sessionid_hashtbl ; 
 int /*<<< orphan*/ * stateid_hashtbl ; 
 int /*<<< orphan*/ * unconf_id_hashtbl ; 
 int /*<<< orphan*/ * unconf_str_hashtbl ; 

int
nfs4_state_init(void)
{
	int i, status;

	status = nfsd4_init_slabs();
	if (status)
		return status;
	for (i = 0; i < CLIENT_HASH_SIZE; i++) {
		INIT_LIST_HEAD(&conf_id_hashtbl[i]);
		INIT_LIST_HEAD(&conf_str_hashtbl[i]);
		INIT_LIST_HEAD(&unconf_str_hashtbl[i]);
		INIT_LIST_HEAD(&unconf_id_hashtbl[i]);
		INIT_LIST_HEAD(&reclaim_str_hashtbl[i]);
	}
	for (i = 0; i < SESSION_HASH_SIZE; i++)
		INIT_LIST_HEAD(&sessionid_hashtbl[i]);
	for (i = 0; i < FILE_HASH_SIZE; i++) {
		INIT_LIST_HEAD(&file_hashtbl[i]);
	}
	for (i = 0; i < OWNER_HASH_SIZE; i++) {
		INIT_LIST_HEAD(&ownerstr_hashtbl[i]);
		INIT_LIST_HEAD(&ownerid_hashtbl[i]);
	}
	for (i = 0; i < STATEID_HASH_SIZE; i++) {
		INIT_LIST_HEAD(&stateid_hashtbl[i]);
		INIT_LIST_HEAD(&lockstateid_hashtbl[i]);
	}
	for (i = 0; i < LOCK_HASH_SIZE; i++) {
		INIT_LIST_HEAD(&lock_ownerid_hashtbl[i]);
		INIT_LIST_HEAD(&lock_ownerstr_hashtbl[i]);
	}
	memset(&onestateid, ~0, sizeof(stateid_t));
	INIT_LIST_HEAD(&close_lru);
	INIT_LIST_HEAD(&client_lru);
	INIT_LIST_HEAD(&del_recall_lru);
	reclaim_str_hashtbl_size = 0;
	return 0;
}