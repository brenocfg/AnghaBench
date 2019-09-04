#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct unpcb {scalar_t__ unp_ino; TYPE_2__* unp_conn; } ;
struct stat64 {scalar_t__ st_ino; void* st_dev; void* st_blksize; } ;
struct stat {scalar_t__ st_ino; void* st_dev; void* st_blksize; } ;
struct TYPE_6__ {scalar_t__ sb_cc; } ;
struct TYPE_4__ {void* sb_hiwat; } ;
struct socket {scalar_t__ so_type; TYPE_3__ so_rcv; TYPE_1__ so_snd; } ;
typedef  scalar_t__ ino_t ;
typedef  scalar_t__ ino64_t ;
typedef  void* blksize_t ;
struct TYPE_5__ {struct socket* unp_socket; } ;

/* Variables and functions */
 int EINVAL ; 
 void* NODEV ; 
 scalar_t__ SOCK_STREAM ; 
 struct unpcb* sotounpcb (struct socket*) ; 
 int /*<<< orphan*/  unp_ino ; 

__attribute__((used)) static int
uipc_sense(struct socket *so, void *ub, int isstat64)
{
	struct unpcb *unp = sotounpcb(so);
	struct socket *so2;
	blksize_t blksize;

	if (unp == 0)
		return (EINVAL);

	blksize = so->so_snd.sb_hiwat;
	if (so->so_type == SOCK_STREAM && unp->unp_conn != 0) {
		so2 = unp->unp_conn->unp_socket;
		blksize += so2->so_rcv.sb_cc;
	}
	if (unp->unp_ino == 0)
		unp->unp_ino = unp_ino++;

	if (isstat64 != 0) {
		struct stat64  *sb64;

		sb64 = (struct stat64 *)ub;
		sb64->st_blksize = blksize;
		sb64->st_dev = NODEV;
		sb64->st_ino = (ino64_t)unp->unp_ino;
	} else {
		struct stat *sb;

		sb = (struct stat *)ub;
		sb->st_blksize = blksize;
		sb->st_dev = NODEV;
		sb->st_ino = (ino_t)(uintptr_t)unp->unp_ino;
	}

	return (0);
}