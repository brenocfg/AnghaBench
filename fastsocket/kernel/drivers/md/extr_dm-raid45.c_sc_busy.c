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
struct TYPE_2__ {int /*<<< orphan*/  stripes; } ;
struct raid_set {TYPE_1__ sc; } ;

/* Variables and functions */
 int STRIPES_MIN ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int sc_active (TYPE_1__*) ; 

__attribute__((used)) static int sc_busy(struct raid_set *rs)
{
	return sc_active(&rs->sc) >
	       atomic_read(&rs->sc.stripes) - (STRIPES_MIN / 2);
}