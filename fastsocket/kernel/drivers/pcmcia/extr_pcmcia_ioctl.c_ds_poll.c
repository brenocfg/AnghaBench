#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct pcmcia_socket* socket; } ;
typedef  TYPE_3__ user_info_t ;
typedef  int u_int ;
struct pcmcia_socket {int /*<<< orphan*/  queue; } ;
struct TYPE_7__ {TYPE_1__* dentry; } ;
struct file {TYPE_3__* private_data; TYPE_2__ f_path; } ;
typedef  int /*<<< orphan*/  poll_table ;
struct TYPE_6__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 scalar_t__ CHECK_USER (TYPE_3__*) ; 
 int POLLERR ; 
 int POLLIN ; 
 int POLLRDNORM ; 
 int /*<<< orphan*/  ds_dbg (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iminor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_empty (TYPE_3__*) ; 

__attribute__((used)) static u_int ds_poll(struct file *file, poll_table *wait)
{
    struct pcmcia_socket *s;
    user_info_t *user;

    ds_dbg(2, "ds_poll(socket %d)\n", iminor(file->f_path.dentry->d_inode));

    user = file->private_data;
    if (CHECK_USER(user))
	return POLLERR;
    s = user->socket;
    /*
     * We don't check for a dead socket here since that
     * will send cardmgr into an endless spin.
     */
    poll_wait(file, &s->queue, wait);
    if (!queue_empty(user))
	return POLLIN | POLLRDNORM;
    return 0;
}