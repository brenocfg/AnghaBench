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
typedef  int /*<<< orphan*/  u16 ;
struct rio_mport {int /*<<< orphan*/ * riores; } ;
struct resource {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t RIO_DOORBELL_RESOURCE ; 
 int /*<<< orphan*/  kfree (struct resource*) ; 
 struct resource* kmalloc (int,int /*<<< orphan*/ ) ; 
 int request_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  rio_init_dbell_res (struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rio_setup_inb_dbell (struct rio_mport*,void*,struct resource*,void (*) (struct rio_mport*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ )) ; 

int rio_request_inb_dbell(struct rio_mport *mport,
			  void *dev_id,
			  u16 start,
			  u16 end,
			  void (*dinb) (struct rio_mport * mport, void *dev_id, u16 src,
					u16 dst, u16 info))
{
	int rc = 0;

	struct resource *res = kmalloc(sizeof(struct resource), GFP_KERNEL);

	if (res) {
		rio_init_dbell_res(res, start, end);

		/* Make sure these doorbells aren't in use */
		if ((rc =
		     request_resource(&mport->riores[RIO_DOORBELL_RESOURCE],
				      res)) < 0) {
			kfree(res);
			goto out;
		}

		/* Hook the doorbell callback */
		rc = rio_setup_inb_dbell(mport, dev_id, res, dinb);
	} else
		rc = -ENOMEM;

      out:
	return rc;
}