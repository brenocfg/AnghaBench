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
struct procdata {int /*<<< orphan*/  rd_queue; struct proc_dir_entry* log; } ;
struct proc_dir_entry {int dummy; } ;
struct log_data {int dummy; } ;
struct TYPE_6__ {TYPE_1__* dentry; } ;
struct file {int f_mode; scalar_t__ private_data; TYPE_2__ f_path; } ;
typedef  int /*<<< orphan*/  poll_table ;
struct TYPE_7__ {struct TYPE_7__* next; struct procdata* proclog; } ;
typedef  TYPE_3__ hysdn_card ;
struct TYPE_5__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 struct proc_dir_entry* PDE (int /*<<< orphan*/ ) ; 
 unsigned int POLLIN ; 
 unsigned int POLLRDNORM ; 
 TYPE_3__* card_root ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int
hysdn_log_poll(struct file *file, poll_table * wait)
{
	unsigned int mask = 0;
	struct proc_dir_entry *pde = PDE(file->f_path.dentry->d_inode);
	hysdn_card *card;
	struct procdata *pd = NULL;

	if ((file->f_mode & (FMODE_READ | FMODE_WRITE)) == FMODE_WRITE)
		return (mask);	/* no polling for write supported */

	/* we need to search the card */
	card = card_root;
	while (card) {
		pd = card->proclog;
		if (pd->log == pde)
			break;
		card = card->next;	/* search next entry */
	}
	if (!card)
		return (mask);	/* card not found */

	poll_wait(file, &(pd->rd_queue), wait);

	if (*((struct log_data **) file->private_data))
		mask |= POLLIN | POLLRDNORM;

	return mask;
}