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
struct xhci_virt_device {int real_port; TYPE_3__* udev; } ;
struct xhci_interval_bw_table {TYPE_2__* interval_bw; } ;
struct xhci_tt_bw_info {int ttport; struct xhci_interval_bw_table bw_table; int /*<<< orphan*/  slot_id; int /*<<< orphan*/  tt_list; } ;
struct xhci_hcd {TYPE_1__* rh_bw; } ;
struct usb_tt {scalar_t__ multi; } ;
struct usb_device {unsigned int maxchild; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_6__ {int /*<<< orphan*/  slot_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  endpoints; } ;
struct TYPE_4__ {int /*<<< orphan*/  tts; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int XHCI_MAX_INTERVAL ; 
 struct xhci_tt_bw_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xhci_free_tt_info (struct xhci_hcd*,struct xhci_virt_device*,int /*<<< orphan*/ ) ; 

int xhci_alloc_tt_info(struct xhci_hcd *xhci,
		struct xhci_virt_device *virt_dev,
		struct usb_device *hdev,
		struct usb_tt *tt, gfp_t mem_flags)
{
	struct xhci_tt_bw_info		*tt_info;
	unsigned int			num_ports;
	int				i, j;

	if (!tt->multi)
		num_ports = 1;
	else
		num_ports = hdev->maxchild;

	for (i = 0; i < num_ports; i++, tt_info++) {
		struct xhci_interval_bw_table *bw_table;

		tt_info = kzalloc(sizeof(*tt_info), mem_flags);
		if (!tt_info)
			goto free_tts;
		INIT_LIST_HEAD(&tt_info->tt_list);
		list_add(&tt_info->tt_list,
				&xhci->rh_bw[virt_dev->real_port - 1].tts);
		tt_info->slot_id = virt_dev->udev->slot_id;
		if (tt->multi)
			tt_info->ttport = i+1;
		bw_table = &tt_info->bw_table;
		for (j = 0; j < XHCI_MAX_INTERVAL; j++)
			INIT_LIST_HEAD(&bw_table->interval_bw[j].endpoints);
	}
	return 0;

free_tts:
	xhci_free_tt_info(xhci, virt_dev, virt_dev->udev->slot_id);
	return -ENOMEM;
}