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
struct pnp_device_id {int dummy; } ;
struct pnp_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  reserve_resources_of_dev (struct pnp_dev*) ; 

__attribute__((used)) static int system_pnp_probe(struct pnp_dev *dev,
			    const struct pnp_device_id *dev_id)
{
	reserve_resources_of_dev(dev);
	return 0;
}