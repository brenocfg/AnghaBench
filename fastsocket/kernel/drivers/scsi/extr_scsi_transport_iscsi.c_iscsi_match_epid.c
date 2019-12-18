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
typedef  scalar_t__ uint64_t ;
struct iscsi_endpoint {scalar_t__ id; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct iscsi_endpoint* iscsi_dev_to_endpoint (struct device*) ; 

__attribute__((used)) static int iscsi_match_epid(struct device *dev, void *data)
{
	struct iscsi_endpoint *ep = iscsi_dev_to_endpoint(dev);
	uint64_t *epid = (uint64_t *) data;

	return *epid == ep->id;
}