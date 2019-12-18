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
struct device {int dummy; } ;
typedef  scalar_t__ ap_qid_t ;
struct TYPE_2__ {scalar_t__ qid; } ;

/* Variables and functions */
 TYPE_1__* to_ap_dev (struct device*) ; 

__attribute__((used)) static int __ap_scan_bus(struct device *dev, void *data)
{
	return to_ap_dev(dev)->qid == (ap_qid_t)(unsigned long) data;
}