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
struct stripe {int /*<<< orphan*/  cnt; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int stripe_ref(struct stripe *stripe)
{
	return atomic_read(&stripe->cnt);
}