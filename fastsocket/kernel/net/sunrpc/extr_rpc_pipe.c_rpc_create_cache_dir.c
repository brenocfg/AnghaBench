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
struct qstr {int dummy; } ;
struct dentry {int dummy; } ;
struct cache_detail {int dummy; } ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  rpc_cachedir_populate ; 
 struct dentry* rpc_mkdir_populate (struct dentry*,struct qstr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct cache_detail*) ; 

struct dentry *rpc_create_cache_dir(struct dentry *parent, struct qstr *name,
				    mode_t umode, struct cache_detail *cd)
{
	return rpc_mkdir_populate(parent, name, umode, NULL,
			rpc_cachedir_populate, cd);
}