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
typedef  struct vnode* vnode_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct vnode {int dummy; } ;
struct vfs_context {int /*<<< orphan*/  vc_ucred; int /*<<< orphan*/  vc_thread; } ;
struct fileproc {TYPE_2__* f_fglob; } ;
typedef  int /*<<< orphan*/  proc_t ;
struct TYPE_3__ {scalar_t__ length; int /*<<< orphan*/  sub_tag; int /*<<< orphan*/  tag; } ;
typedef  TYPE_1__ kd_chunk_header_v3 ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_4__ {int fg_offset; scalar_t__ fg_data; int /*<<< orphan*/  fg_cred; } ;

/* Variables and functions */
 scalar_t__ DTYPE_VNODE ; 
 int EBADF ; 
 int EFAULT ; 
 scalar_t__ FILEGLOB_DTYPE (TYPE_2__*) ; 
 int KERN_SUCCESS ; 
 int RAW_file_offset ; 
 int /*<<< orphan*/  current_proc () ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  fp_drop (int /*<<< orphan*/ ,int,struct fileproc*,int) ; 
 scalar_t__ fp_lookup (int /*<<< orphan*/ ,int,struct fileproc**,int) ; 
 int kdbg_write_to_vnode (int /*<<< orphan*/ ,size_t,struct vnode*,struct vfs_context*,int) ; 
 int /*<<< orphan*/  proc_fdlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_fdunlock (int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_getwithref (struct vnode*) ; 
 int /*<<< orphan*/  vnode_put (struct vnode*) ; 

int
kdbg_write_v3_chunk_to_fd(uint32_t tag, uint32_t sub_tag, uint64_t length, void *payload, uint64_t payload_size, int fd)
{
	proc_t p;
	struct vfs_context context;
	struct fileproc *fp;
	vnode_t vp;
	p = current_proc();

	proc_fdlock(p);
	if ( (fp_lookup(p, fd, &fp, 1)) ) {
		proc_fdunlock(p);
		return EFAULT;
	}

	context.vc_thread = current_thread();
	context.vc_ucred = fp->f_fglob->fg_cred;

	if (FILEGLOB_DTYPE(fp->f_fglob) != DTYPE_VNODE) {
		fp_drop(p, fd, fp, 1);
		proc_fdunlock(p);
		return EBADF;
	}
	vp = (struct vnode *) fp->f_fglob->fg_data;
	proc_fdunlock(p);

	if ( (vnode_getwithref(vp)) == 0 ) {
		RAW_file_offset = fp->f_fglob->fg_offset;

		kd_chunk_header_v3 chunk_header = {
			.tag = tag,
			.sub_tag = sub_tag,
			.length = length,
		};

		int ret = kdbg_write_to_vnode((caddr_t)  &chunk_header, sizeof(kd_chunk_header_v3), vp, &context, RAW_file_offset);
		if (!ret) {
			RAW_file_offset += sizeof(kd_chunk_header_v3);
		}

		ret = kdbg_write_to_vnode((caddr_t) payload, (size_t) payload_size, vp, &context, RAW_file_offset);
		if (!ret) {
			RAW_file_offset  += payload_size;
		}

		fp->f_fglob->fg_offset = RAW_file_offset;
		vnode_put(vp);
	}

	fp_drop(p, fd, fp, 0);
	return KERN_SUCCESS;
}