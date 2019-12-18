#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  conns; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; TYPE_2__ ustats; } ;
struct ip_vs_service {TYPE_3__ stats; } ;
struct ip_vs_conn {TYPE_5__* dest; } ;
struct TYPE_11__ {int /*<<< orphan*/  conns; } ;
struct TYPE_14__ {int /*<<< orphan*/  lock; TYPE_4__ ustats; } ;
struct TYPE_8__ {int /*<<< orphan*/  conns; } ;
struct TYPE_13__ {int /*<<< orphan*/  lock; TYPE_1__ ustats; } ;
struct TYPE_12__ {TYPE_6__ stats; } ;

/* Variables and functions */
 TYPE_7__ ip_vs_stats ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
ip_vs_conn_stats(struct ip_vs_conn *cp, struct ip_vs_service *svc)
{
	spin_lock(&cp->dest->stats.lock);
	cp->dest->stats.ustats.conns++;
	spin_unlock(&cp->dest->stats.lock);

	spin_lock(&svc->stats.lock);
	svc->stats.ustats.conns++;
	spin_unlock(&svc->stats.lock);

	spin_lock(&ip_vs_stats.lock);
	ip_vs_stats.ustats.conns++;
	spin_unlock(&ip_vs_stats.lock);
}