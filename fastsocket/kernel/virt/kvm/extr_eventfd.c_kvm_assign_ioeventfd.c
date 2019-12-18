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
struct kvm_ioeventfd {int flags; int len; scalar_t__ addr; int /*<<< orphan*/  datamatch; int /*<<< orphan*/  fd; } ;
struct kvm {int /*<<< orphan*/  slots_lock; int /*<<< orphan*/  ioeventfds; } ;
struct eventfd_ctx {int dummy; } ;
struct _ioeventfd {scalar_t__ addr; int length; int wildcard; int /*<<< orphan*/  list; int /*<<< orphan*/  dev; int /*<<< orphan*/  datamatch; struct eventfd_ctx* eventfd; } ;
typedef  enum kvm_bus { ____Placeholder_kvm_bus } kvm_bus ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct eventfd_ctx*) ; 
 int KVM_IOEVENTFD_FLAG_DATAMATCH ; 
 int KVM_IOEVENTFD_FLAG_PIO ; 
 int KVM_IOEVENTFD_VALID_FLAG_MASK ; 
 int KVM_MMIO_BUS ; 
 int KVM_PIO_BUS ; 
 int PTR_ERR (struct eventfd_ctx*) ; 
 struct eventfd_ctx* eventfd_ctx_fdget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eventfd_ctx_put (struct eventfd_ctx*) ; 
 scalar_t__ ioeventfd_check_collision (struct kvm*,struct _ioeventfd*) ; 
 int /*<<< orphan*/  ioeventfd_ops ; 
 int /*<<< orphan*/  kfree (struct _ioeventfd*) ; 
 int kvm_io_bus_register_dev (struct kvm*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_iodevice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct _ioeventfd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
kvm_assign_ioeventfd(struct kvm *kvm, struct kvm_ioeventfd *args)
{
	int                       pio = args->flags & KVM_IOEVENTFD_FLAG_PIO;
	enum kvm_bus              bus_idx = pio ? KVM_PIO_BUS : KVM_MMIO_BUS;
	struct _ioeventfd        *p;
	struct eventfd_ctx       *eventfd;
	int                       ret;

	/* must be natural-word sized */
	switch (args->len) {
	case 1:
	case 2:
	case 4:
	case 8:
		break;
	default:
		return -EINVAL;
	}

	/* check for range overflow */
	if (args->addr + args->len < args->addr)
		return -EINVAL;

	/* check for extra flags that we don't understand */
	if (args->flags & ~KVM_IOEVENTFD_VALID_FLAG_MASK)
		return -EINVAL;

	eventfd = eventfd_ctx_fdget(args->fd);
	if (IS_ERR(eventfd))
		return PTR_ERR(eventfd);

	p = kzalloc(sizeof(*p), GFP_KERNEL);
	if (!p) {
		ret = -ENOMEM;
		goto fail;
	}

	INIT_LIST_HEAD(&p->list);
	p->addr    = args->addr;
	p->length  = args->len;
	p->eventfd = eventfd;

	/* The datamatch feature is optional, otherwise this is a wildcard */
	if (args->flags & KVM_IOEVENTFD_FLAG_DATAMATCH)
		p->datamatch = args->datamatch;
	else
		p->wildcard = true;

	mutex_lock(&kvm->slots_lock);

	/* Verify that there isnt a match already */
	if (ioeventfd_check_collision(kvm, p)) {
		ret = -EEXIST;
		goto unlock_fail;
	}

	kvm_iodevice_init(&p->dev, &ioeventfd_ops);

	ret = kvm_io_bus_register_dev(kvm, bus_idx, &p->dev);
	if (ret < 0)
		goto unlock_fail;

	list_add_tail(&p->list, &kvm->ioeventfds);

	mutex_unlock(&kvm->slots_lock);

	return 0;

unlock_fail:
	mutex_unlock(&kvm->slots_lock);

fail:
	kfree(p);
	eventfd_ctx_put(eventfd);

	return ret;
}