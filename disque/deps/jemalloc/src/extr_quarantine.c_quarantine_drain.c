#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_4__ {size_t curbytes; scalar_t__ curobjs; } ;
typedef  TYPE_1__ quarantine_t ;

/* Variables and functions */
 int /*<<< orphan*/  quarantine_drain_one (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
quarantine_drain(tsd_t *tsd, quarantine_t *quarantine, size_t upper_bound)
{

	while (quarantine->curbytes > upper_bound && quarantine->curobjs > 0)
		quarantine_drain_one(tsd, quarantine);
}