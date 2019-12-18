#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;
struct vhost_net {TYPE_1__ dev; } ;
struct socket {int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  fput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 long vhost_dev_check_owner (TYPE_1__*) ; 
 long vhost_dev_reset_owner (TYPE_1__*) ; 
 int /*<<< orphan*/  vhost_net_flush (struct vhost_net*) ; 
 int /*<<< orphan*/  vhost_net_stop (struct vhost_net*,struct socket**,struct socket**) ; 

__attribute__((used)) static long vhost_net_reset_owner(struct vhost_net *n)
{
	struct socket *tx_sock = NULL;
	struct socket *rx_sock = NULL;
	long err;
	mutex_lock(&n->dev.mutex);
	err = vhost_dev_check_owner(&n->dev);
	if (err)
		goto done;
	vhost_net_stop(n, &tx_sock, &rx_sock);
	vhost_net_flush(n);
	err = vhost_dev_reset_owner(&n->dev);
done:
	mutex_unlock(&n->dev.mutex);
	if (tx_sock)
		fput(tx_sock->file);
	if (rx_sock)
		fput(rx_sock->file);
	return err;
}