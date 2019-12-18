#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
struct TYPE_27__ {TYPE_6__* data; } ;
typedef  TYPE_3__ xfs_dabuf_t ;
struct TYPE_28__ {int valuelen; int /*<<< orphan*/ * value; TYPE_2__* dp; int /*<<< orphan*/  rmtblkcnt; scalar_t__ rmtblkno; int /*<<< orphan*/  whichfork; } ;
typedef  TYPE_4__ xfs_da_args_t ;
struct TYPE_29__ {scalar_t__ dupcnt; int (* put_listent ) (TYPE_5__*,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ;scalar_t__ seen_enough; TYPE_2__* dp; scalar_t__ put_value; scalar_t__ resynch; TYPE_10__* cursor; } ;
typedef  TYPE_5__ xfs_attr_list_context_t ;
struct TYPE_25__ {int /*<<< orphan*/  count; } ;
struct TYPE_30__ {TYPE_1__ hdr; TYPE_9__* entries; } ;
typedef  TYPE_6__ xfs_attr_leafblock_t ;
struct TYPE_31__ {scalar_t__ namelen; int /*<<< orphan*/ * name; int /*<<< orphan*/  valueblk; int /*<<< orphan*/  valuelen; } ;
typedef  TYPE_7__ xfs_attr_leaf_name_remote_t ;
struct TYPE_32__ {size_t namelen; int /*<<< orphan*/ * nameval; int /*<<< orphan*/  valuelen; } ;
typedef  TYPE_8__ xfs_attr_leaf_name_local_t ;
struct TYPE_33__ {int flags; int /*<<< orphan*/  hashval; } ;
typedef  TYPE_9__ xfs_attr_leaf_entry_t ;
struct TYPE_24__ {int initted; scalar_t__ hashval; scalar_t__ offset; } ;
typedef  TYPE_10__ attrlist_cursor_kern_t ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_26__ {int /*<<< orphan*/  i_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int KM_NOFS ; 
 int KM_SLEEP ; 
 int /*<<< orphan*/  XFS_ATTR_FORK ; 
 int XFS_ATTR_INCOMPLETE ; 
 int XFS_ATTR_LOCAL ; 
 int /*<<< orphan*/  XFS_B_TO_FSB (int /*<<< orphan*/ ,int) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kmem_alloc (int,int) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (TYPE_5__*,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int stub2 (TYPE_5__*,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int stub3 (TYPE_5__*,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_attr_list_leaf (TYPE_5__*) ; 
 int /*<<< orphan*/  trace_xfs_attr_list_leaf_end (TYPE_5__*) ; 
 int /*<<< orphan*/  trace_xfs_attr_list_notfound (TYPE_5__*) ; 
 TYPE_8__* xfs_attr_leaf_name_local (TYPE_6__*,int) ; 
 TYPE_7__* xfs_attr_leaf_name_remote (TYPE_6__*,int) ; 
 int xfs_attr_rmtval_get (TYPE_4__*) ; 

int
xfs_attr_leaf_list_int(xfs_dabuf_t *bp, xfs_attr_list_context_t *context)
{
	attrlist_cursor_kern_t *cursor;
	xfs_attr_leafblock_t *leaf;
	xfs_attr_leaf_entry_t *entry;
	int retval, i;

	ASSERT(bp != NULL);
	leaf = bp->data;
	cursor = context->cursor;
	cursor->initted = 1;

	trace_xfs_attr_list_leaf(context);

	/*
	 * Re-find our place in the leaf block if this is a new syscall.
	 */
	if (context->resynch) {
		entry = &leaf->entries[0];
		for (i = 0; i < be16_to_cpu(leaf->hdr.count); entry++, i++) {
			if (be32_to_cpu(entry->hashval) == cursor->hashval) {
				if (cursor->offset == context->dupcnt) {
					context->dupcnt = 0;
					break;
				}
				context->dupcnt++;
			} else if (be32_to_cpu(entry->hashval) >
					cursor->hashval) {
				context->dupcnt = 0;
				break;
			}
		}
		if (i == be16_to_cpu(leaf->hdr.count)) {
			trace_xfs_attr_list_notfound(context);
			return(0);
		}
	} else {
		entry = &leaf->entries[0];
		i = 0;
	}
	context->resynch = 0;

	/*
	 * We have found our place, start copying out the new attributes.
	 */
	retval = 0;
	for (  ; (i < be16_to_cpu(leaf->hdr.count)); entry++, i++) {
		if (be32_to_cpu(entry->hashval) != cursor->hashval) {
			cursor->hashval = be32_to_cpu(entry->hashval);
			cursor->offset = 0;
		}

		if (entry->flags & XFS_ATTR_INCOMPLETE)
			continue;		/* skip incomplete entries */

		if (entry->flags & XFS_ATTR_LOCAL) {
			xfs_attr_leaf_name_local_t *name_loc =
				xfs_attr_leaf_name_local(leaf, i);

			retval = context->put_listent(context,
						entry->flags,
						name_loc->nameval,
						(int)name_loc->namelen,
						be16_to_cpu(name_loc->valuelen),
						&name_loc->nameval[name_loc->namelen]);
			if (retval)
				return retval;
		} else {
			xfs_attr_leaf_name_remote_t *name_rmt =
				xfs_attr_leaf_name_remote(leaf, i);

			int valuelen = be32_to_cpu(name_rmt->valuelen);

			if (context->put_value) {
				xfs_da_args_t args;

				memset((char *)&args, 0, sizeof(args));
				args.dp = context->dp;
				args.whichfork = XFS_ATTR_FORK;
				args.valuelen = valuelen;
				args.value = kmem_alloc(valuelen, KM_SLEEP | KM_NOFS);
				args.rmtblkno = be32_to_cpu(name_rmt->valueblk);
				args.rmtblkcnt = XFS_B_TO_FSB(args.dp->i_mount, valuelen);
				retval = xfs_attr_rmtval_get(&args);
				if (retval)
					return retval;
				retval = context->put_listent(context,
						entry->flags,
						name_rmt->name,
						(int)name_rmt->namelen,
						valuelen,
						args.value);
				kmem_free(args.value);
			} else {
				retval = context->put_listent(context,
						entry->flags,
						name_rmt->name,
						(int)name_rmt->namelen,
						valuelen,
						NULL);
			}
			if (retval)
				return retval;
		}
		if (context->seen_enough)
			break;
		cursor->offset++;
	}
	trace_xfs_attr_list_leaf_end(context);
	return(retval);
}