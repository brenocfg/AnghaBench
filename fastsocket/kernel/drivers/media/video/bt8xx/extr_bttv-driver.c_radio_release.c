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
struct saa6588_command {int dummy; } ;
struct file {struct bttv_fh* private_data; } ;
struct bttv_fh {int /*<<< orphan*/  prio; struct bttv* btv; } ;
struct bttv {int /*<<< orphan*/  radio_user; int /*<<< orphan*/  prio; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA6588_CMD_CLOSE ; 
 int /*<<< orphan*/  bttv_call_all (struct bttv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct saa6588_command*) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  ioctl ; 
 int /*<<< orphan*/  kfree (struct bttv_fh*) ; 
 int /*<<< orphan*/  v4l2_prio_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int radio_release(struct file *file)
{
	struct bttv_fh *fh = file->private_data;
	struct bttv *btv = fh->btv;
	struct saa6588_command cmd;

	v4l2_prio_close(&btv->prio, fh->prio);
	file->private_data = NULL;
	kfree(fh);

	btv->radio_user--;

	bttv_call_all(btv, core, ioctl, SAA6588_CMD_CLOSE, &cmd);

	return 0;
}