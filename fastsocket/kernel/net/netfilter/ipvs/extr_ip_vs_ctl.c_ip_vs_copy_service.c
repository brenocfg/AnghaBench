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
struct ip_vs_service_entry {int timeout; int /*<<< orphan*/  stats; int /*<<< orphan*/  num_dests; int /*<<< orphan*/  netmask; int /*<<< orphan*/  flags; int /*<<< orphan*/  sched_name; int /*<<< orphan*/  fwmark; int /*<<< orphan*/  port; int /*<<< orphan*/  addr; int /*<<< orphan*/  protocol; } ;
struct TYPE_3__ {int /*<<< orphan*/  ip; } ;
struct ip_vs_service {int timeout; int /*<<< orphan*/  stats; int /*<<< orphan*/  num_dests; int /*<<< orphan*/  netmask; int /*<<< orphan*/  flags; TYPE_2__* scheduler; int /*<<< orphan*/  fwmark; int /*<<< orphan*/  port; TYPE_1__ addr; int /*<<< orphan*/  protocol; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  ip_vs_copy_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ip_vs_copy_service(struct ip_vs_service_entry *dst, struct ip_vs_service *src)
{
	dst->protocol = src->protocol;
	dst->addr = src->addr.ip;
	dst->port = src->port;
	dst->fwmark = src->fwmark;
	strlcpy(dst->sched_name, src->scheduler->name, sizeof(dst->sched_name));
	dst->flags = src->flags;
	dst->timeout = src->timeout / HZ;
	dst->netmask = src->netmask;
	dst->num_dests = src->num_dests;
	ip_vs_copy_stats(&dst->stats, &src->stats);
}