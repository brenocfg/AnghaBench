#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_deleg_who_type_t ;
struct TYPE_10__ {int /*<<< orphan*/  who_type; int /*<<< orphan*/ * who_deleg_perm_avl; TYPE_1__* who_fsperm; } ;
typedef  TYPE_2__ who_perm_t ;
typedef  int /*<<< orphan*/  uu_avl_t ;
typedef  int /*<<< orphan*/  uu_avl_pool_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_11__ {int /*<<< orphan*/ * fsps_deleg_perm_avl_pool; } ;
typedef  TYPE_3__ fs_perm_set_t ;
struct TYPE_12__ {int /*<<< orphan*/  dpn_avl_node; } ;
typedef  TYPE_4__ deleg_perm_node_t ;
typedef  scalar_t__ data_type_t ;
struct TYPE_9__ {TYPE_3__* fsp_set; } ;

/* Variables and functions */
 scalar_t__ DATA_TYPE_BOOLEAN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_type (int /*<<< orphan*/ *) ; 
 TYPE_4__* safe_malloc (int) ; 
 int /*<<< orphan*/  set_deleg_perm_node (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,char const*,char) ; 
 int /*<<< orphan*/  uu_avl_node_init (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
parse_who_perm(who_perm_t *who_perm, nvlist_t *nvl, char locality)
{
	nvpair_t *nvp = NULL;
	fs_perm_set_t *fspset = who_perm->who_fsperm->fsp_set;
	uu_avl_t *avl = who_perm->who_deleg_perm_avl;
	zfs_deleg_who_type_t who_type = who_perm->who_type;

	while ((nvp = nvlist_next_nvpair(nvl, nvp)) != NULL) {
		const char *name = nvpair_name(nvp);
		data_type_t type = nvpair_type(nvp);
		uu_avl_pool_t *avl_pool = fspset->fsps_deleg_perm_avl_pool;
		deleg_perm_node_t *node =
		    safe_malloc(sizeof (deleg_perm_node_t));

		assert(type == DATA_TYPE_BOOLEAN);

		uu_avl_node_init(node, &node->dpn_avl_node, avl_pool);
		set_deleg_perm_node(avl, node, who_type, name, locality);
	}

	return (0);
}