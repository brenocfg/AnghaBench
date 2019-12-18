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
struct ses_component {scalar_t__ addr; } ;
struct enclosure_device {int components; TYPE_1__* component; } ;
struct efd {scalar_t__ addr; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct ses_component* scratch; } ;

/* Variables and functions */
 int /*<<< orphan*/  enclosure_add_device (struct enclosure_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ses_enclosure_find_by_addr(struct enclosure_device *edev,
				      void *data)
{
	struct efd *efd = data;
	int i;
	struct ses_component *scomp;

	if (!edev->component[0].scratch)
		return 0;

	for (i = 0; i < edev->components; i++) {
		scomp = edev->component[i].scratch;
		if (scomp->addr != efd->addr)
			continue;

		enclosure_add_device(edev, i, efd->dev);
		return 1;
	}
	return 0;
}