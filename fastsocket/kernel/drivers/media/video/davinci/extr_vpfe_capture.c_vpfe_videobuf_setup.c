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
struct vpfe_fh {struct vpfe_device* vpfe_dev; } ;
struct vpfe_device {int /*<<< orphan*/  v4l2_dev; } ;
struct videobuf_queue {struct vpfe_fh* priv_data; } ;
struct TYPE_2__ {unsigned int device_bufsize; unsigned int min_numbuffers; } ;

/* Variables and functions */
 TYPE_1__ config_params ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int vpfe_videobuf_setup(struct videobuf_queue *vq,
				unsigned int *count,
				unsigned int *size)
{
	struct vpfe_fh *fh = vq->priv_data;
	struct vpfe_device *vpfe_dev = fh->vpfe_dev;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_buffer_setup\n");
	*size = config_params.device_bufsize;

	if (*count < config_params.min_numbuffers)
		*count = config_params.min_numbuffers;
	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev,
		"count=%d, size=%d\n", *count, *size);
	return 0;
}