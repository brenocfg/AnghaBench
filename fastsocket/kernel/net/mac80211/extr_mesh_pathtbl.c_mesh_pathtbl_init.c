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
struct mesh_table {void* known_gates; void* mean_chain_len; int /*<<< orphan*/ * copy_node; int /*<<< orphan*/ * free_node; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (void*) ; 
 int /*<<< orphan*/  INIT_PATHS_SIZE_ORDER ; 
 void* MEAN_CHAIN_LEN ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,struct mesh_table*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mesh_path_node_copy ; 
 int /*<<< orphan*/  mesh_path_node_free ; 
 int /*<<< orphan*/  mesh_paths ; 
 struct mesh_table* mesh_table_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mesh_table_free (struct mesh_table*,int) ; 
 int /*<<< orphan*/  mpp_paths ; 

int mesh_pathtbl_init(void)
{
	struct mesh_table *tbl_path, *tbl_mpp;
	int ret;

	tbl_path = mesh_table_alloc(INIT_PATHS_SIZE_ORDER);
	if (!tbl_path)
		return -ENOMEM;
	tbl_path->free_node = &mesh_path_node_free;
	tbl_path->copy_node = &mesh_path_node_copy;
	tbl_path->mean_chain_len = MEAN_CHAIN_LEN;
	tbl_path->known_gates = kzalloc(sizeof(struct hlist_head), GFP_ATOMIC);
	if (!tbl_path->known_gates) {
		ret = -ENOMEM;
		goto free_path;
	}
	INIT_HLIST_HEAD(tbl_path->known_gates);


	tbl_mpp = mesh_table_alloc(INIT_PATHS_SIZE_ORDER);
	if (!tbl_mpp) {
		ret = -ENOMEM;
		goto free_path;
	}
	tbl_mpp->free_node = &mesh_path_node_free;
	tbl_mpp->copy_node = &mesh_path_node_copy;
	tbl_mpp->mean_chain_len = MEAN_CHAIN_LEN;
	tbl_mpp->known_gates = kzalloc(sizeof(struct hlist_head), GFP_ATOMIC);
	if (!tbl_mpp->known_gates) {
		ret = -ENOMEM;
		goto free_mpp;
	}
	INIT_HLIST_HEAD(tbl_mpp->known_gates);

	/* Need no locking since this is during init */
	RCU_INIT_POINTER(mesh_paths, tbl_path);
	RCU_INIT_POINTER(mpp_paths, tbl_mpp);

	return 0;

free_mpp:
	mesh_table_free(tbl_mpp, true);
free_path:
	mesh_table_free(tbl_path, true);
	return ret;
}