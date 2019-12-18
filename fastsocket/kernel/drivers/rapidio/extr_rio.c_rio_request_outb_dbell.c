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
struct rio_dev {int /*<<< orphan*/ * riores; } ;
struct resource {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t RIO_DOORBELL_RESOURCE ; 
 int /*<<< orphan*/  kfree (struct resource*) ; 
 struct resource* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ request_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  rio_init_dbell_res (struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct resource *rio_request_outb_dbell(struct rio_dev *rdev, u16 start,
					u16 end)
{
	struct resource *res = kmalloc(sizeof(struct resource), GFP_KERNEL);

	if (res) {
		rio_init_dbell_res(res, start, end);

		/* Make sure these doorbells aren't in use */
		if (request_resource(&rdev->riores[RIO_DOORBELL_RESOURCE], res)
		    < 0) {
			kfree(res);
			res = NULL;
		}
	}

	return res;
}