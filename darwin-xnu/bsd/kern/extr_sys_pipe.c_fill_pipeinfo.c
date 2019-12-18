#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
struct vinfo_stat {int vst_mode; int vst_blksize; int vst_size; int vst_blocks; int vst_nlink; int /*<<< orphan*/  vst_ctimensec; int /*<<< orphan*/  vst_ctime; int /*<<< orphan*/  vst_mtimensec; int /*<<< orphan*/  vst_mtime; int /*<<< orphan*/  vst_atimensec; int /*<<< orphan*/  vst_atime; int /*<<< orphan*/  vst_gid; int /*<<< orphan*/  vst_uid; } ;
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct pipe_info {int /*<<< orphan*/  pipe_status; void* pipe_peerhandle; void* pipe_handle; struct vinfo_stat pipe_stat; } ;
struct TYPE_2__ {scalar_t__ buffer; int cnt; } ;
struct pipe {int /*<<< orphan*/  pipe_state; struct pipe* pipe_peer; TYPE_1__ pipe_buffer; } ;

/* Variables and functions */
 int EBADF ; 
 int MAX_PIPESIZE (struct pipe*) ; 
 int /*<<< orphan*/  PIPE_LOCK (struct pipe*) ; 
 int PIPE_SIZE ; 
 int /*<<< orphan*/  PIPE_UNLOCK (struct pipe*) ; 
 int S_IFIFO ; 
 int S_IRGRP ; 
 int S_IRUSR ; 
 int S_IWGRP ; 
 int S_IWUSR ; 
 scalar_t__ VM_KERNEL_ADDRPERM (uintptr_t) ; 
 int /*<<< orphan*/  bzero (struct vinfo_stat*,int) ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 int /*<<< orphan*/  kauth_getgid () ; 
 int /*<<< orphan*/  kauth_getuid () ; 
 int mac_pipe_check_stat (int /*<<< orphan*/ ,struct pipe*) ; 
 int /*<<< orphan*/  nanotime (struct timespec*) ; 

int
fill_pipeinfo(struct pipe * cpipe, struct pipe_info * pinfo)
{
#if CONFIG_MACF
        int error;
#endif
	struct timespec now;
	struct vinfo_stat * ub;
	int pipe_size = 0;
	int pipe_count;

	if (cpipe == NULL)
	        return (EBADF);
	PIPE_LOCK(cpipe);

#if CONFIG_MACF
	error = mac_pipe_check_stat(kauth_cred_get(), cpipe);
	if (error) {
		PIPE_UNLOCK(cpipe);
	        return (error);
	}
#endif
	if (cpipe->pipe_buffer.buffer == 0) {
	        /*
		 * must be stat'ing the write fd
		 */
	        if (cpipe->pipe_peer) {
		        /*
			 * the peer still exists, use it's info
			 */
		        pipe_size  = MAX_PIPESIZE(cpipe->pipe_peer);
			pipe_count = cpipe->pipe_peer->pipe_buffer.cnt;
		} else {
			pipe_count = 0;
		}
	} else {
	        pipe_size  = MAX_PIPESIZE(cpipe);
		pipe_count = cpipe->pipe_buffer.cnt;
	}
	/*
	 * since peer's buffer is setup ouside of lock
	 * we might catch it in transient state
	 */
	if (pipe_size == 0)
		pipe_size  = PIPE_SIZE;

	ub = &pinfo->pipe_stat;

	bzero(ub, sizeof(*ub));
	ub->vst_mode = S_IFIFO | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;
	ub->vst_blksize = pipe_size;
	ub->vst_size = pipe_count;
	if (ub->vst_blksize != 0)
		ub->vst_blocks = (ub->vst_size + ub->vst_blksize - 1) / ub->vst_blksize;
	ub->vst_nlink = 1;

	ub->vst_uid = kauth_getuid();
	ub->vst_gid = kauth_getgid();

	nanotime(&now);
	ub->vst_atime  = now.tv_sec;
	ub->vst_atimensec = now.tv_nsec;

	ub->vst_mtime  = now.tv_sec;
	ub->vst_mtimensec = now.tv_nsec;

	ub->vst_ctime  = now.tv_sec;
	ub->vst_ctimensec = now.tv_nsec;

	/*
	 * Left as 0: st_dev, st_ino, st_nlink, st_rdev, st_flags, st_gen, st_uid, st_gid.
	 * XXX (st_dev, st_ino) should be unique.
	 */

	pinfo->pipe_handle = (uint64_t)VM_KERNEL_ADDRPERM((uintptr_t)cpipe);
	pinfo->pipe_peerhandle = (uint64_t)VM_KERNEL_ADDRPERM((uintptr_t)(cpipe->pipe_peer));
	pinfo->pipe_status = cpipe->pipe_state;

	PIPE_UNLOCK(cpipe);

	return (0);
}