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
struct rng_info {int /*<<< orphan*/  rfd; } ;
struct device {struct rng_info* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  device_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  VIRTIO_ID_RNG ; 
 int /*<<< orphan*/  VIRTQUEUE_NUM ; 
 int /*<<< orphan*/  add_virtqueue (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ devices ; 
 struct rng_info* malloc (int) ; 
 struct device* new_device (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_or_die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rng_input ; 
 int /*<<< orphan*/  verbose (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_rng(void)
{
	struct device *dev;
	struct rng_info *rng_info = malloc(sizeof(*rng_info));

	/* Our device's privat info simply contains the /dev/random fd. */
	rng_info->rfd = open_or_die("/dev/random", O_RDONLY);

	/* Create the new device. */
	dev = new_device("rng", VIRTIO_ID_RNG);
	dev->priv = rng_info;

	/* The device has one virtqueue, where the Guest places inbufs. */
	add_virtqueue(dev, VIRTQUEUE_NUM, rng_input);

	verbose("device %u: rng\n", devices.device_num++);
}