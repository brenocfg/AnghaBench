#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vnode {int dummy; } ;
struct vfs_context {int /*<<< orphan*/  vc_ucred; int /*<<< orphan*/  vc_thread; } ;
struct fileproc {TYPE_1__* f_fglob; } ;
struct TYPE_6__ {int /*<<< orphan*/  aio_fildes; } ;
struct TYPE_7__ {int flags; int returnval; TYPE_2__ aiocb; int /*<<< orphan*/  procp; } ;
typedef  TYPE_3__ aio_workq_entry ;
struct TYPE_5__ {int /*<<< orphan*/  fg_cred; } ;

/* Variables and functions */
 int AIO_FSYNC ; 
 int MNT_DWAIT ; 
 int MNT_WAIT ; 
 int VNOP_FSYNC (struct vnode*,int,struct vfs_context*) ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  fp_drop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fileproc*,int /*<<< orphan*/ ) ; 
 int fp_getfvp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fileproc**,struct vnode**) ; 
 int vnode_getwithref (struct vnode*) ; 
 int /*<<< orphan*/  vnode_put (struct vnode*) ; 

__attribute__((used)) static int
do_aio_fsync( aio_workq_entry *entryp )
{
	struct vfs_context 	context;
	struct vnode 		*vp;
	struct fileproc		*fp;
	int			sync_flag;
	int			error;

	/*
	 * We are never called unless either AIO_FSYNC or AIO_DSYNC are set.
	 *
	 * If AIO_DSYNC is set, we can tell the lower layers that it is OK
	 * to mark for update the metadata not strictly necessary for data
	 * retrieval, rather than forcing it to disk.
	 *
	 * If AIO_FSYNC is set, we have to also wait for metadata not really
	 * necessary to data retrival are committed to stable storage (e.g.
	 * atime, mtime, ctime, etc.).
	 *
	 * Metadata necessary for data retrieval ust be committed to stable
	 * storage in either case (file length, etc.).
	 */
	if (entryp->flags & AIO_FSYNC)
		sync_flag = MNT_WAIT;
	else
		sync_flag = MNT_DWAIT;
	
	error = fp_getfvp( entryp->procp, entryp->aiocb.aio_fildes, &fp, &vp);
	if ( error == 0 ) {
		if ( (error = vnode_getwithref(vp)) ) {
		        fp_drop(entryp->procp, entryp->aiocb.aio_fildes, fp, 0);
			entryp->returnval = -1;
			return(error);
		}
		context.vc_thread = current_thread();
		context.vc_ucred = fp->f_fglob->fg_cred;

		error = VNOP_FSYNC( vp, sync_flag, &context);

		(void)vnode_put(vp);

		fp_drop(entryp->procp, entryp->aiocb.aio_fildes, fp, 0);
	}
	if ( error != 0 )
		entryp->returnval = -1;

	return( error );
		
}