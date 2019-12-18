#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  bl_total; int /*<<< orphan*/  bl_min; int /*<<< orphan*/  bl_reaplimit; } ;
struct TYPE_6__ {int /*<<< orphan*/  bl_total; int /*<<< orphan*/  bl_min; int /*<<< orphan*/  bl_reaplimit; } ;
struct TYPE_7__ {int /*<<< orphan*/  mc_bkt_lock; TYPE_1__ mc_empty; TYPE_2__ mc_full; } ;
typedef  TYPE_3__ mcache_t ;

/* Variables and functions */
 int /*<<< orphan*/  MCACHE_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MCACHE_UNLOCK (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mcache_bkt_ws_zero(mcache_t *cp)
{
	MCACHE_LOCK(&cp->mc_bkt_lock);

	cp->mc_full.bl_reaplimit = cp->mc_full.bl_total;
	cp->mc_full.bl_min = cp->mc_full.bl_total;
	cp->mc_empty.bl_reaplimit = cp->mc_empty.bl_total;
	cp->mc_empty.bl_min = cp->mc_empty.bl_total;

	MCACHE_UNLOCK(&cp->mc_bkt_lock);
}