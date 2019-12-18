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
struct tape390_kekl_pair {int /*<<< orphan*/ * kekl; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ check_ext_kekl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_ext_kekl_pair(struct tape390_kekl_pair *kekls)
{
	if (check_ext_kekl(&kekls->kekl[0]))
		goto invalid;
	if (check_ext_kekl(&kekls->kekl[1]))
		goto invalid;

	return 0;
invalid:
	return -EINVAL;
}