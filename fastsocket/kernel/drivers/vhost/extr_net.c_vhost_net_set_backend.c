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
struct vhost_virtqueue {int /*<<< orphan*/  mutex; struct vhost_ubuf_ref* private_data; struct vhost_ubuf_ref* ubufs; } ;
struct vhost_ubuf_ref {int /*<<< orphan*/  file; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct vhost_net {TYPE_1__ dev; struct vhost_virtqueue* vqs; } ;
struct socket {int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOBUFS ; 
 scalar_t__ IS_ERR (struct vhost_ubuf_ref*) ; 
 int PTR_ERR (struct vhost_ubuf_ref*) ; 
 unsigned int VHOST_NET_VQ_MAX ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ ) ; 
 struct vhost_ubuf_ref* get_socket (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct vhost_ubuf_ref*,struct vhost_ubuf_ref*) ; 
 int vhost_dev_check_owner (TYPE_1__*) ; 
 int vhost_init_used (struct vhost_virtqueue*) ; 
 int /*<<< orphan*/  vhost_net_disable_vq (struct vhost_net*,struct vhost_virtqueue*) ; 
 int /*<<< orphan*/  vhost_net_enable_vq (struct vhost_net*,struct vhost_virtqueue*) ; 
 int /*<<< orphan*/  vhost_net_flush_vq (struct vhost_net*,unsigned int) ; 
 scalar_t__ vhost_sock_zcopy (struct vhost_ubuf_ref*) ; 
 struct vhost_ubuf_ref* vhost_ubuf_alloc (struct vhost_virtqueue*,int) ; 
 int /*<<< orphan*/  vhost_ubuf_put_and_wait (struct vhost_ubuf_ref*) ; 
 int /*<<< orphan*/  vhost_vq_access_ok (struct vhost_virtqueue*) ; 
 int /*<<< orphan*/  vhost_zerocopy_signal_used (struct vhost_virtqueue*) ; 

__attribute__((used)) static long vhost_net_set_backend(struct vhost_net *n, unsigned index, int fd)
{
	struct socket *sock, *oldsock;
	struct vhost_virtqueue *vq;
	struct vhost_ubuf_ref *ubufs, *oldubufs = NULL;
	int r;

	mutex_lock(&n->dev.mutex);
	r = vhost_dev_check_owner(&n->dev);
	if (r)
		goto err;

	if (index >= VHOST_NET_VQ_MAX) {
		r = -ENOBUFS;
		goto err;
	}
	vq = n->vqs + index;
	mutex_lock(&vq->mutex);

	/* Verify that ring has been setup correctly. */
	if (!vhost_vq_access_ok(vq)) {
		r = -EFAULT;
		goto err_vq;
	}
	sock = get_socket(fd);
	if (IS_ERR(sock)) {
		r = PTR_ERR(sock);
		goto err_vq;
	}

	/* start polling new socket */
	oldsock = vq->private_data;
	if (sock != oldsock) {
		ubufs = vhost_ubuf_alloc(vq, sock && vhost_sock_zcopy(sock));
		if (IS_ERR(ubufs)) {
			r = PTR_ERR(ubufs);
			goto err_ubufs;
		}
		oldubufs = vq->ubufs;
		vq->ubufs = ubufs;
		vhost_net_disable_vq(n, vq);
		rcu_assign_pointer(vq->private_data, sock);
		vhost_net_enable_vq(n, vq);

		r = vhost_init_used(vq);
		if (r)
			goto err_vq;
	}

	mutex_unlock(&vq->mutex);

	if (oldubufs) {
		vhost_ubuf_put_and_wait(oldubufs);
		mutex_lock(&vq->mutex);
		vhost_zerocopy_signal_used(vq);
		mutex_unlock(&vq->mutex);
	}

	if (oldsock) {
		vhost_net_flush_vq(n, index);
		fput(oldsock->file);
	}

	mutex_unlock(&n->dev.mutex);
	return 0;

err_ubufs:
	fput(sock->file);
err_vq:
	mutex_unlock(&vq->mutex);
err:
	mutex_unlock(&n->dev.mutex);
	return r;
}