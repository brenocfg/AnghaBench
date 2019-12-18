#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qstr {char const* name; int /*<<< orphan*/  len; int /*<<< orphan*/  hash; } ;
struct dentry {int dummy; } ;
struct TYPE_3__ {struct dentry* dir; } ;
struct TYPE_4__ {TYPE_1__ pipefs; } ;
struct cache_detail {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  full_name_hash (char const*,int /*<<< orphan*/ ) ; 
 struct dentry* rpc_create_cache_dir (struct dentry*,struct qstr*,int /*<<< orphan*/ ,struct cache_detail*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  sunrpc_destroy_cache_detail (struct cache_detail*) ; 
 int /*<<< orphan*/  sunrpc_init_cache_detail (struct cache_detail*) ; 

int sunrpc_cache_register_pipefs(struct dentry *parent,
				 const char *name, mode_t umode,
				 struct cache_detail *cd)
{
	struct qstr q;
	struct dentry *dir;
	int ret = 0;

	sunrpc_init_cache_detail(cd);
	q.name = name;
	q.len = strlen(name);
	q.hash = full_name_hash(q.name, q.len);
	dir = rpc_create_cache_dir(parent, &q, umode, cd);
	if (!IS_ERR(dir))
		cd->u.pipefs.dir = dir;
	else {
		sunrpc_destroy_cache_detail(cd);
		ret = PTR_ERR(dir);
	}
	return ret;
}