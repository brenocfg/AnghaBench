#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ user_magic; struct TYPE_6__* next; struct pcmcia_socket* socket; } ;
typedef  TYPE_2__ user_info_t ;
struct TYPE_5__ {scalar_t__ busy; } ;
struct pcmcia_socket {TYPE_2__* user; TYPE_1__ pcmcia_state; } ;
struct inode {int dummy; } ;
struct file {int f_flags; TYPE_2__* private_data; } ;

/* Variables and functions */
 scalar_t__ CHECK_USER (TYPE_2__*) ; 
 int O_ACCMODE ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  ds_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iminor (struct inode*) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  pcmcia_put_socket (struct pcmcia_socket*) ; 

__attribute__((used)) static int ds_release(struct inode *inode, struct file *file)
{
    struct pcmcia_socket *s;
    user_info_t *user, **link;

    ds_dbg(0, "ds_release(socket %d)\n", iminor(inode));

    user = file->private_data;
    if (CHECK_USER(user))
	goto out;

    s = user->socket;

    /* Unlink user data structure */
    if ((file->f_flags & O_ACCMODE) != O_RDONLY) {
	s->pcmcia_state.busy = 0;
    }
    file->private_data = NULL;
    for (link = &s->user; *link; link = &(*link)->next)
	if (*link == user) break;
    if (link == NULL)
	goto out;
    *link = user->next;
    user->user_magic = 0;
    kfree(user);
    pcmcia_put_socket(s);
out:
    return 0;
}