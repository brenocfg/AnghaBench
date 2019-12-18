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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int u32_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct zsWlanDev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  zm_assert (int) ; 

u16_t zfiGlobalDataSize(zdev_t *dev)
{
	u32_t ret;
	ret = (sizeof(struct zsWlanDev));
	zm_assert((ret>>16) == 0);
	return (u16_t)ret;
}