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
typedef  int /*<<< orphan*/  uio_t ;
typedef  int /*<<< orphan*/  uio_buf ;
typedef  int uint32_t ;
typedef  int u_int32_t ;
struct vnode {int dummy; } ;
struct vfs_context {int /*<<< orphan*/  vc_ucred; int /*<<< orphan*/  vc_thread; } ;
struct quotafile {int qf_maxentries; int /*<<< orphan*/  qf_entrycnt; int /*<<< orphan*/  qf_shift; int /*<<< orphan*/  qf_cred; struct vnode* qf_vp; } ;
struct dqblk {int dqb_id; int dqb_ihardlimit; int dqb_isoftlimit; int dqb_curinodes; int dqb_btime; int dqb_itime; void* dqb_curbytes; void* dqb_bsoftlimit; void* dqb_bhardlimit; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_USER_ADDR_T (struct dqblk*) ; 
 int EIO ; 
 int OSSwapBigToHostInt32 (int) ; 
 void* OSSwapBigToHostInt64 (void*) ; 
 int OSSwapHostToBigInt32 (int) ; 
 int /*<<< orphan*/  UIO_READ ; 
 int UIO_SIZEOF (int) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int VNOP_READ (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vfs_context*) ; 
 int VNOP_WRITE (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vfs_context*) ; 
 int /*<<< orphan*/  bzero (struct dqblk*,int) ; 
 int /*<<< orphan*/  current_thread () ; 
 int dqhash1 (int,int /*<<< orphan*/ ,int) ; 
 int dqhash2 (int,int) ; 
 int /*<<< orphan*/  dqoffset (int) ; 
 int /*<<< orphan*/  printf (char*,int,int,...) ; 
 int /*<<< orphan*/  qf_lock (struct quotafile*) ; 
 int /*<<< orphan*/  qf_unlock (struct quotafile*) ; 
 int /*<<< orphan*/  uio_addiov (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uio_createwithbuffer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  uio_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uio_resid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dqlookup(struct quotafile *qfp, u_int32_t id, struct dqblk *dqb, uint32_t *index)
{
	struct vnode *dqvp;
	struct vfs_context context;
	uio_t auio;
	int i, skip, last;
	u_int32_t mask;
	int error = 0;
	char uio_buf[ UIO_SIZEOF(1) ];


	qf_lock(qfp);

	dqvp = qfp->qf_vp;

	context.vc_thread = current_thread();
	context.vc_ucred = qfp->qf_cred;

	mask = qfp->qf_maxentries - 1;
	i = dqhash1(id, qfp->qf_shift, mask);
	skip = dqhash2(id, mask);

	for (last = (i + (qfp->qf_maxentries-1) * skip) & mask;
	     i != last;
	     i = (i + skip) & mask) {
		auio = uio_createwithbuffer(1, dqoffset(i), UIO_SYSSPACE, UIO_READ, 
									  &uio_buf[0], sizeof(uio_buf));
		uio_addiov(auio, CAST_USER_ADDR_T(dqb), sizeof (struct dqblk));
		error = VNOP_READ(dqvp, auio, 0, &context);
		if (error) {
			printf("dqlookup: error %d looking up id %u at index %d\n", error, id, i);
			break;
		} else if (uio_resid(auio)) {
			error = EIO;
			printf("dqlookup: error looking up id %u at index %d\n", id, i);
			break;
		}
		/*
		 * An empty entry means there is no entry
		 * with that id.  In this case a new dqb
		 * record will be inserted.
		 */
		if (dqb->dqb_id == 0) {
			bzero(dqb, sizeof(struct dqblk));
			dqb->dqb_id = OSSwapHostToBigInt32(id);
			/*
			 * Write back to reserve entry for this id
			 */
			uio_reset(auio, dqoffset(i), UIO_SYSSPACE, UIO_WRITE);
			uio_addiov(auio, CAST_USER_ADDR_T(dqb), sizeof (struct dqblk));
			error = VNOP_WRITE(dqvp, auio, 0, &context);
			if (uio_resid(auio) && error == 0)
				error = EIO;
			if (error == 0)
				++qfp->qf_entrycnt;
			dqb->dqb_id = id;
			break;
		}
		/* An id match means an entry was found. */
		if (OSSwapBigToHostInt32(dqb->dqb_id) == id) {
			dqb->dqb_bhardlimit = OSSwapBigToHostInt64(dqb->dqb_bhardlimit);
			dqb->dqb_bsoftlimit = OSSwapBigToHostInt64(dqb->dqb_bsoftlimit);
			dqb->dqb_curbytes   = OSSwapBigToHostInt64(dqb->dqb_curbytes);
			dqb->dqb_ihardlimit = OSSwapBigToHostInt32(dqb->dqb_ihardlimit);
			dqb->dqb_isoftlimit = OSSwapBigToHostInt32(dqb->dqb_isoftlimit);
			dqb->dqb_curinodes  = OSSwapBigToHostInt32(dqb->dqb_curinodes);
			dqb->dqb_btime      = OSSwapBigToHostInt32(dqb->dqb_btime);
			dqb->dqb_itime      = OSSwapBigToHostInt32(dqb->dqb_itime);
			dqb->dqb_id         = OSSwapBigToHostInt32(dqb->dqb_id);
			break;
		}
	}
	qf_unlock(qfp);

	*index = i;  /* remember index so we don't have to recompute it later */

	return (error);
}