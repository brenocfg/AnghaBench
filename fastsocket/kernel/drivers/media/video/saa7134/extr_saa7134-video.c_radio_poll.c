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
struct saa7134_fh {struct saa7134_dev* dev; } ;
struct saa7134_dev {int dummy; } ;
struct saa6588_command {unsigned int result; int /*<<< orphan*/ * event_list; struct file* instance; } ;
struct file {struct saa7134_fh* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 unsigned int ENODEV ; 
 int /*<<< orphan*/  SAA6588_CMD_POLL ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  ioctl ; 
 int /*<<< orphan*/  saa_call_all (struct saa7134_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct saa6588_command*) ; 

__attribute__((used)) static unsigned int radio_poll(struct file *file, poll_table *wait)
{
	struct saa7134_fh *fh = file->private_data;
	struct saa7134_dev *dev = fh->dev;
	struct saa6588_command cmd;

	cmd.instance = file;
	cmd.event_list = wait;
	cmd.result = -ENODEV;
	saa_call_all(dev, core, ioctl, SAA6588_CMD_POLL, &cmd);

	return cmd.result;
}