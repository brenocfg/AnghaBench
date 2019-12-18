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
struct zoneref {int dummy; } ;
struct zonelist {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void zlc_mark_zone_full(struct zonelist *zonelist, struct zoneref *z)
{
}