#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * swbuf; int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ vwsnd_port_t ;
struct TYPE_5__ {TYPE_1__ wport; TYPE_1__ rport; } ;
typedef  TYPE_2__ vwsnd_dev_t ;
struct poll_table_struct {int dummy; } ;
struct file {int f_mode; scalar_t__ private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DBGEV (char*,struct file*,struct poll_table_struct*) ; 
 int /*<<< orphan*/  DBGPV (char*,unsigned int) ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLRDNORM ; 
 unsigned int POLLWRNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 
 scalar_t__ swb_inc_u (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int vwsnd_audio_poll(struct file *file,
				     struct poll_table_struct *wait)
{
	vwsnd_dev_t *devc = (vwsnd_dev_t *) file->private_data;
	vwsnd_port_t *rport = (file->f_mode & FMODE_READ) ?
		&devc->rport : NULL;
	vwsnd_port_t *wport = (file->f_mode & FMODE_WRITE) ?
		&devc->wport : NULL;
	unsigned int mask = 0;

	DBGEV("(file=0x%p, wait=0x%p)\n", file, wait);

	ASSERT(rport || wport);
	if (rport) {
		poll_wait(file, &rport->queue, wait);
		if (swb_inc_u(rport, 0))
			mask |= (POLLIN | POLLRDNORM);
	}
	if (wport) {
		poll_wait(file, &wport->queue, wait);
		if (wport->swbuf == NULL || swb_inc_u(wport, 0))
			mask |= (POLLOUT | POLLWRNORM);
	}

	DBGPV("returning 0x%x\n", mask);
	return mask;
}