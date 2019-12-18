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
struct vring_used_elem {unsigned int id; scalar_t__ len; } ;
struct vhost_virtqueue {unsigned int num; scalar_t__ iov; int /*<<< orphan*/  dev; } ;
struct vhost_log {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (scalar_t__) ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int UIO_MAXIOV ; 
 scalar_t__ iov_length (scalar_t__,unsigned int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vhost_discard_vq_desc (struct vhost_virtqueue*,int) ; 
 int vhost_get_vq_desc (int /*<<< orphan*/ ,struct vhost_virtqueue*,scalar_t__,scalar_t__,unsigned int*,unsigned int*,struct vhost_log*,unsigned int*) ; 
 int /*<<< orphan*/  vq_err (struct vhost_virtqueue*,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static int get_rx_bufs(struct vhost_virtqueue *vq,
		       struct vring_used_elem *heads,
		       int datalen,
		       unsigned *iovcount,
		       struct vhost_log *log,
		       unsigned *log_num,
		       unsigned int quota)
{
	unsigned int out, in;
	int seg = 0;
	int headcount = 0;
	unsigned d;
	int r, nlogs = 0;

	while (datalen > 0 && headcount < quota) {
		if (unlikely(seg >= UIO_MAXIOV)) {
			r = -ENOBUFS;
			goto err;
		}
		r = vhost_get_vq_desc(vq->dev, vq, vq->iov + seg,
				      ARRAY_SIZE(vq->iov) - seg, &out,
				      &in, log, log_num);
		if (unlikely(r < 0))
			goto err;

		d = r;
		if (d == vq->num) {
			r = 0;
			goto err;
		}
		if (unlikely(out || in <= 0)) {
			vq_err(vq, "unexpected descriptor format for RX: "
				"out %d, in %d\n", out, in);
			r = -EINVAL;
			goto err;
		}
		if (unlikely(log)) {
			nlogs += *log_num;
			log += *log_num;
		}
		heads[headcount].id = d;
		heads[headcount].len = iov_length(vq->iov + seg, in);
		datalen -= heads[headcount].len;
		++headcount;
		seg += in;
	}
	heads[headcount - 1].len += datalen;
	*iovcount = seg;
	if (unlikely(log))
		*log_num = nlogs;

	/* Detect overrun */
	if (unlikely(datalen > 0)) {
		r = UIO_MAXIOV + 1;
		goto err;
	}
	return headcount;
err:
	vhost_discard_vq_desc(vq, headcount);
	return r;
}