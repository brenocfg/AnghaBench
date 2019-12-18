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
struct TYPE_2__ {int /*<<< orphan*/  sk; struct file* file; } ;
struct tun_struct {int /*<<< orphan*/  dev; TYPE_1__ socket; struct tun_file* tfile; } ;
struct tun_file {int /*<<< orphan*/  count; struct tun_struct* tun; } ;
struct file {struct tun_file* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_lock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_unlock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_hold (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tun_attach(struct tun_struct *tun, struct file *file)
{
	struct tun_file *tfile = file->private_data;
	int err;

	ASSERT_RTNL();

	netif_tx_lock_bh(tun->dev);

	err = -EINVAL;
	if (tfile->tun)
		goto out;

	err = -EBUSY;
	if (tun->tfile)
		goto out;

	err = 0;
	tfile->tun = tun;
	tun->tfile = tfile;
	tun->socket.file = file;
	dev_hold(tun->dev);
	sock_hold(tun->socket.sk);
	atomic_inc(&tfile->count);

out:
	netif_tx_unlock_bh(tun->dev);
	return err;
}