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
struct stripe {int /*<<< orphan*/  sc; } ;
struct TYPE_2__ {scalar_t__ io_count; } ;
struct raid_set {TYPE_1__ recover; } ;

/* Variables and functions */
 scalar_t__ IO_RECOVER ; 
 scalar_t__ IO_WORK ; 
 struct raid_set* RS (int /*<<< orphan*/ ) ; 
 scalar_t__ StripeRecover (struct stripe*) ; 
 int /*<<< orphan*/  atomic_inc (scalar_t__) ; 

__attribute__((used)) static void recover_io_count(struct stripe *stripe)
{
	struct raid_set *rs = RS(stripe->sc);

	atomic_inc(rs->recover.io_count +
		   (StripeRecover(stripe) ? IO_RECOVER : IO_WORK));
}