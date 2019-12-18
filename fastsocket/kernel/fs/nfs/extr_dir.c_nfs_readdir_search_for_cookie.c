#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct nfs_open_dir_context {scalar_t__ attr_gencount; int duped; scalar_t__ dup_cookie; } ;
struct nfs_inode {scalar_t__ attr_gencount; int cache_validity; } ;
struct nfs_cache_array {int size; scalar_t__ eof_index; scalar_t__ last_cookie; TYPE_8__* array; } ;
struct TYPE_12__ {scalar_t__* dir_cookie; scalar_t__ current_index; int cache_entry_index; int eof; TYPE_9__* file; } ;
typedef  TYPE_10__ nfs_readdir_descriptor_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_14__ {TYPE_1__* dentry; } ;
struct TYPE_21__ {scalar_t__ f_pos; TYPE_6__* f_dentry; struct nfs_open_dir_context* private_data; TYPE_2__ f_path; } ;
struct TYPE_19__ {int /*<<< orphan*/  name; } ;
struct TYPE_20__ {scalar_t__ cookie; TYPE_7__ string; } ;
struct TYPE_17__ {int /*<<< orphan*/  name; } ;
struct TYPE_18__ {TYPE_5__ d_name; TYPE_4__* d_parent; } ;
struct TYPE_15__ {int /*<<< orphan*/  name; } ;
struct TYPE_16__ {TYPE_3__ d_name; } ;
struct TYPE_13__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBADCOOKIE ; 
 int ELOOP ; 
 struct nfs_inode* NFS_I (int /*<<< orphan*/ ) ; 
 int NFS_INO_INVALID_ATTR ; 
 int NFS_INO_INVALID_DATA ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ printk_ratelimit () ; 

__attribute__((used)) static
int nfs_readdir_search_for_cookie(struct nfs_cache_array *array, nfs_readdir_descriptor_t *desc)
{
	int i;
	loff_t new_pos;
	int status = -EAGAIN;

	for (i = 0; i < array->size; i++) {
		if (array->array[i].cookie == *desc->dir_cookie) {
			struct nfs_inode *nfsi = NFS_I(desc->file->f_path.dentry->d_inode);
			struct nfs_open_dir_context *ctx = desc->file->private_data;

			new_pos = desc->current_index + i;
			if (ctx->attr_gencount != nfsi->attr_gencount
			    || (nfsi->cache_validity & (NFS_INO_INVALID_ATTR|NFS_INO_INVALID_DATA))) {
				ctx->duped = 0;
				ctx->attr_gencount = nfsi->attr_gencount;
			} else if (new_pos < desc->file->f_pos) {
				if (ctx->duped > 0
				    && ctx->dup_cookie == *desc->dir_cookie) {
					if (printk_ratelimit()) {
						pr_notice("NFS: directory %s/%s contains a readdir loop."
								"Please contact your server vendor.  "
								"The file: %s has duplicate cookie %llu\n",
								desc->file->f_dentry->d_parent->d_name.name,
								desc->file->f_dentry->d_name.name,
								array->array[i].string.name,
								*desc->dir_cookie);
					}
					status = -ELOOP;
					goto out;
				}
				ctx->dup_cookie = *desc->dir_cookie;
				ctx->duped = -1;
			}
			desc->file->f_pos = new_pos;
			desc->cache_entry_index = i;
			return 0;
		}
	}
	if (array->eof_index >= 0) {
		status = -EBADCOOKIE;
		if (*desc->dir_cookie == array->last_cookie)
			desc->eof = 1;
	}
out:
	return status;
}