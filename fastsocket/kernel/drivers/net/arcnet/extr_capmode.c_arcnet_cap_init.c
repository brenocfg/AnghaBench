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

/* Variables and functions */
 int /*<<< orphan*/ * arc_bcast_proto ; 
 int /*<<< orphan*/ * arc_proto_default ; 
 int /*<<< orphan*/ ** arc_proto_map ; 
 int /*<<< orphan*/ * arc_raw_proto ; 
 int /*<<< orphan*/  capmode_proto ; 

__attribute__((used)) static void arcnet_cap_init(void)
{
	int count;

	for (count = 1; count <= 8; count++)
		if (arc_proto_map[count] == arc_proto_default)
			arc_proto_map[count] = &capmode_proto;

	/* for cap mode, we only set the bcast proto if there's no better one */
	if (arc_bcast_proto == arc_proto_default)
		arc_bcast_proto = &capmode_proto;

	arc_proto_default = &capmode_proto;
	arc_raw_proto = &capmode_proto;
}