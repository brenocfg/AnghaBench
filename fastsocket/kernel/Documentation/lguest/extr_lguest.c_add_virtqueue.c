#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int num; int pfn; scalar_t__ irq; } ;
struct virtqueue {void (* service ) (struct virtqueue*) ;struct virtqueue* next; TYPE_2__ config; int /*<<< orphan*/  vring; scalar_t__ thread; struct device* dev; scalar_t__ last_avail_idx; } ;
struct device {struct virtqueue* vq; TYPE_1__* desc; int /*<<< orphan*/  num_vq; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_6__ {int /*<<< orphan*/  next_irq; } ;
struct TYPE_4__ {scalar_t__ config_len; scalar_t__ feature_len; int /*<<< orphan*/  num_vq; } ;

/* Variables and functions */
 int /*<<< orphan*/  LGUEST_VRING_ALIGN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  device_config (struct device*) ; 
 TYPE_3__ devices ; 
 void* get_pages (unsigned int) ; 
 int getpagesize () ; 
 struct virtqueue* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int to_guest_phys (void*) ; 
 int /*<<< orphan*/  verbose (char*,int) ; 
 int /*<<< orphan*/  vring_init (int /*<<< orphan*/ *,unsigned int,void*,int /*<<< orphan*/ ) ; 
 int vring_size (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_virtqueue(struct device *dev, unsigned int num_descs,
			  void (*service)(struct virtqueue *))
{
	unsigned int pages;
	struct virtqueue **i, *vq = malloc(sizeof(*vq));
	void *p;

	/* First we need some memory for this virtqueue. */
	pages = (vring_size(num_descs, LGUEST_VRING_ALIGN) + getpagesize() - 1)
		/ getpagesize();
	p = get_pages(pages);

	/* Initialize the virtqueue */
	vq->next = NULL;
	vq->last_avail_idx = 0;
	vq->dev = dev;

	/*
	 * This is the routine the service thread will run, and its Process ID
	 * once it's running.
	 */
	vq->service = service;
	vq->thread = (pid_t)-1;

	/* Initialize the configuration. */
	vq->config.num = num_descs;
	vq->config.irq = devices.next_irq++;
	vq->config.pfn = to_guest_phys(p) / getpagesize();

	/* Initialize the vring. */
	vring_init(&vq->vring, num_descs, p, LGUEST_VRING_ALIGN);

	/*
	 * Append virtqueue to this device's descriptor.  We use
	 * device_config() to get the end of the device's current virtqueues;
	 * we check that we haven't added any config or feature information
	 * yet, otherwise we'd be overwriting them.
	 */
	assert(dev->desc->config_len == 0 && dev->desc->feature_len == 0);
	memcpy(device_config(dev), &vq->config, sizeof(vq->config));
	dev->num_vq++;
	dev->desc->num_vq++;

	verbose("Virtqueue page %#lx\n", to_guest_phys(p));

	/*
	 * Add to tail of list, so dev->vq is first vq, dev->vq->next is
	 * second.
	 */
	for (i = &dev->vq; *i; i = &(*i)->next);
	*i = vq;
}