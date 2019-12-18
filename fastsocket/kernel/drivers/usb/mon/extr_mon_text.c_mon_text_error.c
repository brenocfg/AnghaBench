#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct urb {TYPE_4__* ep; TYPE_3__* dev; } ;
struct TYPE_6__ {TYPE_1__* m_bus; } ;
struct mon_reader_text {scalar_t__ nevents; int /*<<< orphan*/  wait; int /*<<< orphan*/  e_list; TYPE_2__ r; int /*<<< orphan*/  e_slab; } ;
struct mon_event_text {char type; unsigned long id; int status; char setup_flag; char data_flag; int /*<<< orphan*/  e_link; scalar_t__ length; scalar_t__ tstamp; int /*<<< orphan*/  is_in; int /*<<< orphan*/  xfertype; int /*<<< orphan*/  epnum; int /*<<< orphan*/  devnum; scalar_t__ busnum; } ;
struct TYPE_8__ {int /*<<< orphan*/  desc; } ;
struct TYPE_7__ {int /*<<< orphan*/  devnum; } ;
struct TYPE_5__ {int /*<<< orphan*/  cnt_text_lost; } ;

/* Variables and functions */
 scalar_t__ EVENT_MAX ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct mon_event_text* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_endpoint_num (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_endpoint_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_urb_dir_in (struct urb*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mon_text_error(void *data, struct urb *urb, int error)
{
	struct mon_reader_text *rp = data;
	struct mon_event_text *ep;

	if (rp->nevents >= EVENT_MAX ||
	    (ep = kmem_cache_alloc(rp->e_slab, GFP_ATOMIC)) == NULL) {
		rp->r.m_bus->cnt_text_lost++;
		return;
	}

	ep->type = 'E';
	ep->id = (unsigned long) urb;
	ep->busnum = 0;
	ep->devnum = urb->dev->devnum;
	ep->epnum = usb_endpoint_num(&urb->ep->desc);
	ep->xfertype = usb_endpoint_type(&urb->ep->desc);
	ep->is_in = usb_urb_dir_in(urb);
	ep->tstamp = 0;
	ep->length = 0;
	ep->status = error;

	ep->setup_flag = '-';
	ep->data_flag = 'E';

	rp->nevents++;
	list_add_tail(&ep->e_link, &rp->e_list);
	wake_up(&rp->wait);
}