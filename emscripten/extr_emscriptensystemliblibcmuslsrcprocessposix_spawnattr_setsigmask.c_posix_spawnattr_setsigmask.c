#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_3__ {int /*<<< orphan*/  __mask; } ;
typedef  TYPE_1__ posix_spawnattr_t ;

/* Variables and functions */

int posix_spawnattr_setsigmask(posix_spawnattr_t *restrict attr, const sigset_t *restrict mask)
{
	attr->__mask = *mask;
	return 0;
}