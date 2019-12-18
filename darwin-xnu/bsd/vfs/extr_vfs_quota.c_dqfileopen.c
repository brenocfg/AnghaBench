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
struct vfs_context {int /*<<< orphan*/  vc_ucred; int /*<<< orphan*/  vc_thread; } ;
struct quotafile {int qf_btime; int qf_itime; int qf_maxentries; int qf_entrycnt; int /*<<< orphan*/  qf_shift; int /*<<< orphan*/  qf_vp; int /*<<< orphan*/  qf_cred; } ;
struct dqfilehdr {scalar_t__ dqh_magic; scalar_t__ dqh_version; scalar_t__ dqh_maxentries; scalar_t__ dqh_btime; scalar_t__ dqh_itime; scalar_t__ dqh_entrycnt; } ;
struct dqblk {int dummy; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  header ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_USER_ADDR_T (struct dqfilehdr*) ; 
 int EINVAL ; 
 int MAX_DQ_TIME ; 
 int MAX_IQ_TIME ; 
 int OSSwapBigToHostInt32 (scalar_t__) ; 
 int QF_VERSION ; 
 int /*<<< orphan*/  UIO_READ ; 
 int UIO_SIZEOF (int) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int VNOP_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vfs_context*) ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  dqhashshift (int) ; 
 int /*<<< orphan*/  powerof2 (int) ; 
 int* quotamagic ; 
 int /*<<< orphan*/  uio_addiov (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uio_createwithbuffer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ uio_resid (int /*<<< orphan*/ ) ; 
 int vnode_size (int /*<<< orphan*/ ,int*,struct vfs_context*) ; 

int
dqfileopen(struct quotafile *qfp, int type)
{
	struct dqfilehdr header;
	struct vfs_context context;
	off_t file_size;
	uio_t auio;
	int error = 0;
	char uio_buf[ UIO_SIZEOF(1) ];

	context.vc_thread = current_thread();
	context.vc_ucred = qfp->qf_cred;
	
	/* Obtain the file size */
	if ((error = vnode_size(qfp->qf_vp, &file_size, &context)) != 0)
	        goto out;

	/* Read the file header */
	auio = uio_createwithbuffer(1, 0, UIO_SYSSPACE, UIO_READ, 
				    &uio_buf[0], sizeof(uio_buf));
	uio_addiov(auio, CAST_USER_ADDR_T(&header), sizeof (header));
	error = VNOP_READ(qfp->qf_vp, auio, 0, &context);
	if (error)
	        goto out;
	else if (uio_resid(auio)) {
		error = EINVAL;
		goto out;
	}
	/* Sanity check the quota file header. */
	if ((OSSwapBigToHostInt32(header.dqh_magic) != quotamagic[type]) ||
	    (OSSwapBigToHostInt32(header.dqh_version) > QF_VERSION) ||
	    (!powerof2(OSSwapBigToHostInt32(header.dqh_maxentries))) ||
	    (OSSwapBigToHostInt32(header.dqh_maxentries) > (file_size / sizeof(struct dqblk)))) {
		error = EINVAL;
		goto out;
	}
	/* Set up the time limits for this quota. */
	if (header.dqh_btime != 0)
		qfp->qf_btime = OSSwapBigToHostInt32(header.dqh_btime);
	else
		qfp->qf_btime = MAX_DQ_TIME;
	if (header.dqh_itime != 0)
		qfp->qf_itime = OSSwapBigToHostInt32(header.dqh_itime);
	else
		qfp->qf_itime = MAX_IQ_TIME;

	/* Calculate the hash table constants. */
	qfp->qf_maxentries = OSSwapBigToHostInt32(header.dqh_maxentries);
	qfp->qf_entrycnt = OSSwapBigToHostInt32(header.dqh_entrycnt);
	qfp->qf_shift = dqhashshift(qfp->qf_maxentries);
out:
	return (error);
}