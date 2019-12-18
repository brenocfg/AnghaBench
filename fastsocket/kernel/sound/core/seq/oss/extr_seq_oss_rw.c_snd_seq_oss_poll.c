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
struct seq_oss_devinfo {int /*<<< orphan*/  cseq; int /*<<< orphan*/  file_mode; scalar_t__ writeq; scalar_t__ readq; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLRDNORM ; 
 unsigned int POLLWRNORM ; 
 scalar_t__ is_read_mode (int /*<<< orphan*/ ) ; 
 scalar_t__ is_write_mode (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_seq_kernel_client_write_poll (int /*<<< orphan*/ ,struct file*,int /*<<< orphan*/ *) ; 
 scalar_t__ snd_seq_oss_readq_poll (scalar_t__,struct file*,int /*<<< orphan*/ *) ; 

unsigned int
snd_seq_oss_poll(struct seq_oss_devinfo *dp, struct file *file, poll_table * wait)
{
	unsigned int mask = 0;

	/* input */
	if (dp->readq && is_read_mode(dp->file_mode)) {
		if (snd_seq_oss_readq_poll(dp->readq, file, wait))
			mask |= POLLIN | POLLRDNORM;
	}

	/* output */
	if (dp->writeq && is_write_mode(dp->file_mode)) {
		if (snd_seq_kernel_client_write_poll(dp->cseq, file, wait))
			mask |= POLLOUT | POLLWRNORM;
	}
	return mask;
}