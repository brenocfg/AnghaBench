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
struct ppp_file {scalar_t__ kind; scalar_t__ dead; int /*<<< orphan*/  rq; int /*<<< orphan*/  rwait; } ;
struct ppp {scalar_t__ n_channels; int flags; } ;
struct file {struct ppp_file* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 scalar_t__ INTERFACE ; 
 struct ppp* PF_TO_PPP (struct ppp_file*) ; 
 unsigned int POLLHUP ; 
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLRDNORM ; 
 unsigned int POLLWRNORM ; 
 int SC_LOOP_TRAFFIC ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ skb_peek (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int ppp_poll(struct file *file, poll_table *wait)
{
	struct ppp_file *pf = file->private_data;
	unsigned int mask;

	if (!pf)
		return 0;
	poll_wait(file, &pf->rwait, wait);
	mask = POLLOUT | POLLWRNORM;
	if (skb_peek(&pf->rq))
		mask |= POLLIN | POLLRDNORM;
	if (pf->dead)
		mask |= POLLHUP;
	else if (pf->kind == INTERFACE) {
		/* see comment in ppp_read */
		struct ppp *ppp = PF_TO_PPP(pf);
		if (ppp->n_channels == 0
		    && (ppp->flags & SC_LOOP_TRAFFIC) == 0)
			mask |= POLLIN | POLLRDNORM;
	}

	return mask;
}