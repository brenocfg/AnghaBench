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
struct subchannel_id {int ssid; int sch_no; } ;
struct idset {int dummy; } ;

/* Variables and functions */
 int idset_get_first (struct idset*,int*,int*) ; 
 int /*<<< orphan*/  init_subchannel_id (struct subchannel_id*) ; 

int idset_sch_get_first(struct idset *set, struct subchannel_id *schid)
{
	int ssid = 0;
	int id = 0;
	int rc;

	rc = idset_get_first(set, &ssid, &id);
	if (rc) {
		init_subchannel_id(schid);
		schid->ssid = ssid;
		schid->sch_no = id;
	}
	return rc;
}