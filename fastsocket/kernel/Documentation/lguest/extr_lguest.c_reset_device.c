#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  num; } ;
struct TYPE_3__ {scalar_t__ desc; } ;
struct virtqueue {scalar_t__ thread; TYPE_2__ config; TYPE_1__ vring; struct virtqueue* next; } ;
struct device {int running; struct virtqueue* vq; scalar_t__ feature_len; int /*<<< orphan*/  name; } ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  lg_last_avail ;

/* Variables and functions */
 int /*<<< orphan*/  LGUEST_VRING_ALIGN ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGTERM ; 
 void* SIG_IGN ; 
 scalar_t__ get_feature_bits (struct device*) ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ kill_launcher ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  verbose (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ vring_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitpid (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reset_device(struct device *dev)
{
	struct virtqueue *vq;

	verbose("Resetting device %s\n", dev->name);

	/* Clear any features they've acked. */
	memset(get_feature_bits(dev) + dev->feature_len, 0, dev->feature_len);

	/* We're going to be explicitly killing threads, so ignore them. */
	signal(SIGCHLD, SIG_IGN);

	/* Zero out the virtqueues, get rid of their threads */
	for (vq = dev->vq; vq; vq = vq->next) {
		if (vq->thread != (pid_t)-1) {
			kill(vq->thread, SIGTERM);
			waitpid(vq->thread, NULL, 0);
			vq->thread = (pid_t)-1;
		}
		memset(vq->vring.desc, 0,
		       vring_size(vq->config.num, LGUEST_VRING_ALIGN));
		lg_last_avail(vq) = 0;
	}
	dev->running = false;

	/* Now we care if threads die. */
	signal(SIGCHLD, (void *)kill_launcher);
}