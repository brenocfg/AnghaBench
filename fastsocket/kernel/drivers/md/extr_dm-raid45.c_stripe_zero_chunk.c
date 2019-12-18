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
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct stripe {TYPE_1__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  stripe_zero_pl_part (struct stripe*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stripe_zero_chunk(struct stripe *stripe, int p)
{
	if (p > -1)
		stripe_zero_pl_part(stripe, p, 0, stripe->io.size);
}