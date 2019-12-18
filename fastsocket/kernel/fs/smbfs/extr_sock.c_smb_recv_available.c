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
struct socket {TYPE_1__* ops; } ;
struct smb_sb_info {int dummy; } ;
typedef  int /*<<< orphan*/  mm_segment_t ;
struct TYPE_2__ {int (* ioctl ) (struct socket*,int /*<<< orphan*/ ,unsigned long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCINQ ; 
 int /*<<< orphan*/  get_ds () ; 
 int /*<<< orphan*/  get_fs () ; 
 struct socket* server_sock (struct smb_sb_info*) ; 
 int /*<<< orphan*/  set_fs (int /*<<< orphan*/ ) ; 
 int stub1 (struct socket*,int /*<<< orphan*/ ,unsigned long) ; 

int
smb_recv_available(struct smb_sb_info *server)
{
	mm_segment_t oldfs;
	int avail, err;
	struct socket *sock = server_sock(server);

	oldfs = get_fs();
	set_fs(get_ds());
	err = sock->ops->ioctl(sock, SIOCINQ, (unsigned long) &avail);
	set_fs(oldfs);
	return (err >= 0) ? avail : err;
}