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
struct saa6588_command {unsigned int result; int /*<<< orphan*/ * event_list; struct file* instance; } ;
struct file {struct bttv_fh* private_data; } ;
struct bttv_fh {struct bttv* btv; } ;
struct bttv {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 unsigned int ENODEV ; 
 int /*<<< orphan*/  SAA6588_CMD_POLL ; 
 int /*<<< orphan*/  bttv_call_all (struct bttv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct saa6588_command*) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  ioctl ; 

__attribute__((used)) static unsigned int radio_poll(struct file *file, poll_table *wait)
{
	struct bttv_fh *fh = file->private_data;
	struct bttv *btv = fh->btv;
	struct saa6588_command cmd;
	cmd.instance = file;
	cmd.event_list = wait;
	cmd.result = -ENODEV;
	bttv_call_all(btv, core, ioctl, SAA6588_CMD_POLL, &cmd);

	return cmd.result;
}