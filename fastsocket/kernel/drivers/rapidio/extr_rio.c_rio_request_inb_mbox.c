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
struct rio_mport {TYPE_1__* inb_msg; int /*<<< orphan*/ * riores; } ;
struct resource {int dummy; } ;
struct TYPE_2__ {void (* mcback ) (struct rio_mport*,void*,int,int) ;struct resource* res; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t RIO_INB_MBOX_RESOURCE ; 
 int /*<<< orphan*/  kfree (struct resource*) ; 
 struct resource* kmalloc (int,int /*<<< orphan*/ ) ; 
 int request_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  rio_init_mbox_res (struct resource*,int,int) ; 
 int rio_open_inb_mbox (struct rio_mport*,void*,int,int) ; 

int rio_request_inb_mbox(struct rio_mport *mport,
			 void *dev_id,
			 int mbox,
			 int entries,
			 void (*minb) (struct rio_mport * mport, void *dev_id, int mbox,
				       int slot))
{
	int rc = 0;

	struct resource *res = kmalloc(sizeof(struct resource), GFP_KERNEL);

	if (res) {
		rio_init_mbox_res(res, mbox, mbox);

		/* Make sure this mailbox isn't in use */
		if ((rc =
		     request_resource(&mport->riores[RIO_INB_MBOX_RESOURCE],
				      res)) < 0) {
			kfree(res);
			goto out;
		}

		mport->inb_msg[mbox].res = res;

		/* Hook the inbound message callback */
		mport->inb_msg[mbox].mcback = minb;

		rc = rio_open_inb_mbox(mport, dev_id, mbox, entries);
	} else
		rc = -ENOMEM;

      out:
	return rc;
}