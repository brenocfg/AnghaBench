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
struct stripe {int /*<<< orphan*/  sc; } ;
struct TYPE_3__ {unsigned int raid_devs; } ;
struct TYPE_4__ {TYPE_1__ set; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK (struct stripe*,unsigned int) ; 
 TYPE_2__* RS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetChunkIo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stripe_allow_io(struct stripe *stripe)
{
	unsigned p = RS(stripe->sc)->set.raid_devs;

	while (p--)
		SetChunkIo(CHUNK(stripe, p));
}