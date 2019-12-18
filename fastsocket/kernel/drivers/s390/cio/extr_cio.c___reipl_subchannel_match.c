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
struct subchannel_id {scalar_t__ ssid; } ;
struct TYPE_3__ {scalar_t__ st; scalar_t__ dev; scalar_t__ dnv; } ;
struct schib {TYPE_1__ pmcw; } ;
struct TYPE_4__ {scalar_t__ devno; scalar_t__ ssid; } ;
struct sch_match_id {scalar_t__ rc; struct subchannel_id schid; TYPE_2__ devid; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ SUBCHANNEL_TYPE_IO ; 
 scalar_t__ stsch_reset (struct subchannel_id,struct schib*) ; 

__attribute__((used)) static int __reipl_subchannel_match(struct subchannel_id schid, void *data)
{
	struct schib schib;
	struct sch_match_id *match_id = data;

	if (stsch_reset(schid, &schib))
		return -ENXIO;
	if ((schib.pmcw.st == SUBCHANNEL_TYPE_IO) && schib.pmcw.dnv &&
	    (schib.pmcw.dev == match_id->devid.devno) &&
	    (schid.ssid == match_id->devid.ssid)) {
		match_id->schid = schid;
		match_id->rc = 0;
		return 1;
	}
	return 0;
}