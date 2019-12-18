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
struct TYPE_4__ {int size; int /*<<< orphan*/  list; scalar_t__ map; } ;
struct mthca_dev {int active; TYPE_2__ catas_err; int /*<<< orphan*/  ib_dev; } ;
struct TYPE_3__ {scalar_t__ port_num; } ;
struct ib_event {TYPE_1__ element; int /*<<< orphan*/  event; int /*<<< orphan*/ * device; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_EVENT_DEVICE_FATAL ; 
#define  MTHCA_CATAS_TYPE_DDR 131 
#define  MTHCA_CATAS_TYPE_INTERNAL 130 
#define  MTHCA_CATAS_TYPE_PARITY 129 
#define  MTHCA_CATAS_TYPE_UPLINK 128 
 int /*<<< orphan*/  catas_list ; 
 int /*<<< orphan*/  catas_lock ; 
 scalar_t__ catas_reset_disable ; 
 int /*<<< orphan*/  catas_work ; 
 int /*<<< orphan*/  catas_wq ; 
 int /*<<< orphan*/  ib_dispatch_event (struct ib_event*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mthca_err (struct mthca_dev*,char*,...) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int swab32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_catas(struct mthca_dev *dev)
{
	struct ib_event event;
	unsigned long flags;
	const char *type;
	int i;

	event.device = &dev->ib_dev;
	event.event  = IB_EVENT_DEVICE_FATAL;
	event.element.port_num = 0;
	dev->active = false;

	ib_dispatch_event(&event);

	switch (swab32(readl(dev->catas_err.map)) >> 24) {
	case MTHCA_CATAS_TYPE_INTERNAL:
		type = "internal error";
		break;
	case MTHCA_CATAS_TYPE_UPLINK:
		type = "uplink bus error";
		break;
	case MTHCA_CATAS_TYPE_DDR:
		type = "DDR data error";
		break;
	case MTHCA_CATAS_TYPE_PARITY:
		type = "internal parity error";
		break;
	default:
		type = "unknown error";
		break;
	}

	mthca_err(dev, "Catastrophic error detected: %s\n", type);
	for (i = 0; i < dev->catas_err.size; ++i)
		mthca_err(dev, "  buf[%02x]: %08x\n",
			  i, swab32(readl(dev->catas_err.map + i)));

	if (catas_reset_disable)
		return;

	spin_lock_irqsave(&catas_lock, flags);
	list_add(&dev->catas_err.list, &catas_list);
	queue_work(catas_wq, &catas_work);
	spin_unlock_irqrestore(&catas_lock, flags);
}