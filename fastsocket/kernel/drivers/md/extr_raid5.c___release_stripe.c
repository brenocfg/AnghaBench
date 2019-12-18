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
struct stripe_head {int /*<<< orphan*/  count; } ;
struct r5conf {int dummy; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_release_stripe (struct r5conf*,struct stripe_head*) ; 

__attribute__((used)) static void __release_stripe(struct r5conf *conf, struct stripe_head *sh)
{
	if (atomic_dec_and_test(&sh->count))
		do_release_stripe(conf, sh);
}