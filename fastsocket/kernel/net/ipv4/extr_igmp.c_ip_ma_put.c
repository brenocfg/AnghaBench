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
struct ip_mc_list {int /*<<< orphan*/  interface; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ip_mc_list*) ; 

__attribute__((used)) static void ip_ma_put(struct ip_mc_list *im)
{
	if (atomic_dec_and_test(&im->refcnt)) {
		in_dev_put(im->interface);
		kfree(im);
	}
}